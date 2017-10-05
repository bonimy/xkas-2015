#include "compress.h"

int Decompress(BYTE* dest, const int dlen, const BYTE *src, const int slen)
{
	int sindex = 0, dindex = 0, clen;

	while (sindex < slen)
	{
		if (src[sindex] == 0xFF)
			return dindex;

        // Command is three most significant bits
        int command = src[sindex] >> 5;

        // Signifies extended length copy.
		if (command == 7)
		{
            // Get new command
			command = (src[sindex] >> 2) & 0x07;
			if (command == 7)
				return 0;

            // Length is ten least significant bits.
			clen = ((src[sindex] & 0x03) << CHAR_BIT);
            clen |= src[++sindex];
		}
		else
			clen = src[sindex] & 0x1F;
		
		clen++;
		sindex++;

		switch (command)
		{
		case 0: // Direct byte copy
			if (dest)
			{
				if (dindex + clen > dlen)
					return 0;
				if (sindex + clen > slen)
					return 0;
				memcpy(dest + dindex, src + sindex, clen);
			}
			dindex += clen;
			sindex += clen;
			continue;
		case 1: // Fill with one byte repeated
			if (dest)
			{
				if (dindex + clen > dlen)
					return 0;
				if (sindex >= slen)
					return 0;
				memset(dest + dindex, src[sindex], clen);
			}
			dindex += clen;
			sindex++;
			continue;
		case 2: // Fill with two alternating bytes
			if (dest)
			{
				if (dindex + clen > dlen)
					return 0;
				if (sindex + 1 >= slen)
					return 0;
				memset(dest + dindex, src[sindex], clen);
				for (int i = 1, j = src[sindex + 1]; i < clen; i += 2)
					dest[dindex + i] = j;
			}
			dindex += clen;
			sindex += 2;
			continue;
		case 3: // Fill with incrementing byte value
			if (dest)
			{
				if (dindex + clen > dlen)
					return 0;
				if (sindex >= slen)
					return 0;
				for (int i = 0, j = src[sindex]; i < clen; i++, j++)
					dest[dindex + i] = j;
			}
			dindex += clen;
			sindex++;
			continue;
		case 4: // Copy data from previous section
			if (dest)
			{
				if (dindex + clen > dlen)
					return 0;
				if (sindex + 1 >= slen)
					return 0;
				memcpy(dest + dindex, dest + ((src[sindex] << CHAR_BIT) | src[sindex + 1]), clen);
			}
			dindex += clen;
			sindex += 2;
			continue;
        case 5:
		case 6:
            return 0;
		default:
			ASSUME(0);
			return 0;
		}
	}
	return 0;
}

suffixtree *tree = new suffixtree();

int LZ2Compress(BYTE *dest, const int dlen, const BYTE *src, const int slen)
{
    // Current source and position index
	int sindex = 0, dindex = 0;
    // Command code, argument length, argument value
	int command = 0, len = 0, value = 0;
    // last command performed
    int lcommand = 0;
    /*
     * lcommand determines when it is efficient to switch to a new command.
     * We think of data starting as
     *  00 FF 60 FF 70
     * Naively, we see an alternating byte repeat at index 1 of length 3. We
     * could encode the first four bytes as
     *  00 00 42 FF 60
     * However, we can also directly write this as
     *  03 FF 60 FF 70
     * While this does not affect the size, it does affect the decompress time, which,
     * for the SNES, is vital to minimize. The latter compression is favored here because it
     * doesn't cost space, but it saves computation.
     */
    
    tree->createtree(src, slen);
    node** children = tree->getchildren();

    while (sindex < slen)
    {
        int tindex = -1;
        int tlen = -1;
        tree->getlongestsubstring(sindex, tindex, tlen);
        sindex++;
    }

    while (sindex < slen)
    {
        byte val0 = src[sindex];

        if (sindex + 1 < slen)
        {
            byte val1 = src[sindex + 1];

            // We need to read the next two bytes
            if (sindex + 2 < slen)
            {
                byte val2 = src[sindex + 2];

                // Get index and length of longest substring
                int tindex = -1;
                int tlen = 0;
                node* child = children[val0];
                do
                {
                    if (child->start >= sindex)
                        break;

                    len += tree->getedge(child);
                    tindex = child->start;
                    if (sindex + len >= slen)
                        break;

                    child = child->getchild(src[sindex + len]);
                } while (child);

                // Word fill sequence (or byte fill)
                if (val2 == val0)
                {
                    len = 3;
                    // Do byte fill instead if three repeated bytes
                    if (val0 == val1)
                        goto _command1;

                    // last command was a direct byte copy
                    if (lcommand == 0)
                    {
                        if (sindex + 3 < slen)
                        {
                            if (src[sindex + 3] == val1)
                            {
                                len = 4;
                                goto _command2;
                            }
                        }

                        // No other commands will occur because val2 == val0. So we can just skip.
                        goto _skip;
                    }

                _command2:
                    for (; sindex + len < slen; len++)
                    {
                        if (src[sindex + len] != val1)
                            break;
                        if (sindex + ++len >= slen)
                            break;
                        if (src[sindex + len] != val0)
                            break;
                    }

                    value = val0 | (val1 << CHAR_BIT);
                    command = 2;
                    goto _write;
                } // val2 != val0
            } // sindex + 2 >= slen

            // Repeating byte sequence
            if (val1 == val0)
            {
                if (lcommand == 0)
                {
                    // This case would have been verified in the alternating bytes case
                    goto _skip;
                }
                len = 2;

            _command1:
                for (; sindex + len < slen; len++)
                    if (src[sindex + len] != val0)
                        break;

                value = val0;
                command = 1;
                goto _write;
            } // val0 != val1

            // Increasing byte sequence
            if (val1 == (BYTE)(val0 + 1))
            {
                len = 2;
                if (lcommand == 0)
                {
                    if (sindex + 2 < slen)
                    {
                        if (src[sindex + 2] == val0 + 2)
                        {
                            len = 3;
                            goto _command3;
                        }
                    }

                    goto _skip;
                }

            _command3:
                for (; sindex + len < slen; len++)
                    if (src[sindex + len] != (BYTE)(val0 + len))
                        break;

                value = val0;
                command = 3;
                goto _write;
            } // val1 != (BYTE)(val0 + 1)
        } // sindex + 1 >= slen

    _skip:
        lcommand = 0;
        sindex++;
        continue;

    // When we are at the end of the sequence.
    _last:
		sindex = slen;

    _write:
		for (int zlen = sindex; zlen > 0; )
		{
			int sublen = min(zlen, 0x400);

			if(dest)
			{
				if (sublen > 0x20)
				{
					if (dindex + 2 + sublen-- > dlen)
						return 0;
					dest[dindex++] = (0x07 << (CHAR_BIT - 3)) | (sublen >> CHAR_BIT);
					dest[dindex++] = sublen++;
				}
				else
				{
					if (dindex + 1 + sublen-- > dlen)
						return 0;
					dest[dindex++] = sublen++;
				}
				memcpy(dest + dindex, src, sublen);
			}
			else if (sublen > 0x20)
				dindex += 2;
			else
				dindex++;

			dindex += sublen;
			zlen -= sublen;
		}

		len--;
		while (len >= 0)
		{
			int sublen = (len & 0x3FF) + 1;

			static const int valsize[] = {-1, 1, 2, 1, 2};
			if (dest)
			{
				if (sublen > 0x20)
				{
					if (dindex + 2 + valsize[command] + 1 > dlen)
						return 0;
					dest[dindex++] = (0x07 << (CHAR_BIT - 3)) | (command << 2) | (--sublen >> CHAR_BIT);
					dest[dindex++] = sublen++;
				}
				else
				{
					if (dindex + 1 + valsize[command] + 1 > dlen)
						return 0;
					--sublen;
					dest[dindex++] = (command << (CHAR_BIT - 3)) | sublen++;
				}

				switch (command)
				{
				case 1:
				case 3:
					dest[dindex++] = value;
					break;
				case 2:
					dest[dindex++] = value;
					dest[dindex++] = value >> CHAR_BIT;
					break;
				case 4:
					dest[dindex++] = value >> CHAR_BIT;
					dest[dindex++] = value;
					value += sublen;
					break;
				default:
					ASSUME(0);
					return 0;
				}
			}
			else
			{
				if (sublen > 0x20)
					dindex += 2;
				else
					dindex++;

				dindex += valsize[command];
			}

			sindex += sublen;
			len -= sublen;
            lcommand = command;
		}
	}

	if (dest)
		dest[dindex] = 0xFF;

	return ++dindex;
}