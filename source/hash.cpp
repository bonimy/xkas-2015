#include "hash.h"

OPFXN(badhash)
{
	return FALSE;
}

const hashtable hashfunctions[] = {badhash, badhash, fxn_php, badhash, badhash, fxn_pla, fxn_wdm, fxn_and,
	fxn_beq, badhash, badhash, badhash, badhash, fxn_rtl, badhash, badhash, badhash, badhash, fxn_stz,
	fxn_dec, fxn_bne, fxn_tdc, badhash, badhash, badhash, fxn_bpl, fxn_txy, fxn_rol, fxn_pld, badhash,
	badhash, badhash, badhash, fxn_tya, badhash, badhash, badhash, badhash, badhash, badhash, badhash,
	badhash, fxn_inc, badhash, badhash, badhash, badhash, badhash, badhash, fxn_stp, badhash, badhash,
	badhash, fxn_tcd, badhash, badhash, badhash, fxn_bcc, badhash, badhash, badhash, badhash, badhash,
	badhash, badhash, badhash, badhash, badhash, badhash, fxn_ora, badhash, fxn_phy, fxn_bcs, fxn_ror,
	badhash, fxn_bmi, fxn_mvp, badhash, badhash, fxn_tsb, fxn_dey, badhash, fxn_xce, badhash, fxn_brl,
	badhash, badhash, badhash, badhash, badhash, badhash, fxn_sep, badhash, badhash, badhash, badhash,
	badhash, badhash, badhash, fxn_sec, badhash, badhash, badhash, fxn_iny, badhash, badhash, badhash,
	badhash, badhash, badhash, fxn_phb, badhash, badhash, badhash, badhash, fxn_org, badhash, badhash,
	fxn_sty, badhash, fxn_plp, badhash, badhash, badhash, badhash, badhash, badhash, badhash, badhash,
	fxn_pei, fxn_cpy, badhash, badhash, fxn_bvc, fxn_cmp, fxn_adc, badhash, badhash, badhash, badhash,
	fxn_tsx, badhash, badhash, badhash, fxn_nop, fxn_sei, badhash, fxn_ldy, fxn_bvs, fxn_bit, badhash,
	badhash, badhash, badhash, badhash, fxn_tay, fxn_wai, badhash, badhash, fxn_lsr, badhash, badhash,
	fxn_asl, badhash, badhash, fxn_txa, badhash, badhash, fxn_tcs, badhash, badhash, fxn_phx, fxn_sbc,
	badhash, fxn_cld, badhash, badhash, badhash, badhash, fxn_phk, fxn_dex, badhash, badhash, badhash,
	fxn_brk, badhash, badhash, badhash, badhash, fxn_ply, badhash, badhash, badhash, fxn_cop, badhash,
	badhash, badhash, badhash, fxn_per, badhash, badhash, badhash, badhash, fxn_inx, badhash, badhash,
	badhash, badhash, badhash, badhash, fxn_pha, fxn_trb, badhash, badhash, badhash, fxn_bra, badhash,
	badhash, fxn_stx, fxn_eor, badhash, badhash, badhash, badhash, badhash, badhash, badhash, badhash,
	fxn_plb, badhash, fxn_cpx, badhash, badhash, fxn_phd, badhash, badhash, badhash, badhash, badhash,
	badhash, badhash, badhash, badhash, badhash, badhash, badhash, badhash, fxn_ldx, badhash, badhash,
	badhash, badhash, badhash, badhash, badhash, fxn_tax, fxn_jsr, fxn_sta, badhash, badhash, badhash,
	badhash, badhash, badhash, badhash, badhash, badhash, badhash, badhash, badhash, badhash, badhash,
	badhash, badhash, fxn_clc, badhash, fxn_mvn, badhash, badhash, fxn_jmp, badhash, badhash, fxn_rts,
	fxn_pea, badhash, badhash, fxn_lda, badhash, badhash, fxn_plx, badhash, fxn_xba, badhash, badhash,
	badhash, badhash, badhash, badhash, badhash, badhash, badhash, fxn_rep, fxn_tsc, fxn_txs, badhash,
	badhash, badhash, badhash, badhash, badhash, badhash, badhash, fxn_clv, fxn_rti, badhash, badhash,
	badhash, fxn_tyx, badhash, badhash, fxn_cli, badhash, fxn_sed, };
