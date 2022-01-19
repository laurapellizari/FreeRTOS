#ifndef INC_2329_H
#define INC_2329_H

/* DATA TYPES MIGHT NOT BE CORRECT. */

#define BASE2329 0xFF0000

/* Definitions for GPIO. */

#define P1DDR	( *( ( volatile unsigned char * ) 0xFFFEB0 ) )
#define P1DR	( *( ( volatile unsigned char * ) 0xFFFF60 ) )
#define PORT1	( *( ( volatile unsigned char * ) 0xFFFF50 ) )
#define P2DDR	( *( ( volatile unsigned char * ) 0xFFFEB1 ) )
#define P2DR	( *( ( volatile unsigned char * ) 0xFFFF61 ) )
#define PORT2	( *( ( volatile unsigned char * ) 0xFFFF51 ) )
#define P3DDR	( *( ( volatile unsigned char * ) 0xFFFEB2 ) )
#define P3DR	( *( ( volatile unsigned char * ) 0xFFFF62 ) )
#define PORT3	( *( ( volatile unsigned char * ) 0xFFFF52 ) )
#define P3ODR	( *( ( volatile unsigned char * ) 0xFFFF76 ) )
#define PORT4	( *( ( volatile unsigned char * ) 0xFFFF53 ) )
#define P5DDR	( *( ( volatile unsigned char * ) 0xFFFEB4 ) )
#define P5DR	( *( ( volatile unsigned char * ) 0xFFFF64 ) )
#define PORT5	( *( ( volatile unsigned char * ) 0xFFFF54 ) )
#define PFCR2	( *( ( volatile unsigned char * ) 0xFFFFAC ) )
#define SYSCR	( *( ( volatile unsigned char * ) 0xFFFF39 ) )
#define P6DDR	( *( ( volatile unsigned char * ) 0xFFFEB5 ) )
#define P6DR	( *( ( volatile unsigned char * ) 0xFFFF65 ) )
#define PORT6	( *( ( volatile unsigned char * ) 0xFFFF55 ) )
#define PFCR2	( *( ( volatile unsigned char * ) 0xFFFFAC ) )
#define PADDR	( *( ( volatile unsigned char * ) 0xFFFEB9 ) )
#define PADR	( *( ( volatile unsigned char * ) 0xFFFF69 ) )
#define PORTA	( *( ( volatile unsigned char * ) 0xFFFF59 ) )
#define PAPCR	( *( ( volatile unsigned char * ) 0xFFFF70 ) )
#define PAODR	( *( ( volatile unsigned char * ) 0xFFFF77 ) )
#define PFCR1	( *( ( volatile unsigned char * ) 0xFFFF45 ) )
#define PBDDR	( *( ( volatile unsigned char * ) 0xFFFEBA ) )
#define PBDR	( *( ( volatile unsigned char * ) 0xFFFF6A ) )
#define PORTB	( *( ( volatile unsigned char * ) 0xFFFF5A ) )
#define PBPCR	( *( ( volatile unsigned char * ) 0xFFFF71 ) )
#define PCDDR	( *( ( volatile unsigned char * ) 0xFFFEBB ) )
#define PCDR	( *( ( volatile unsigned char * ) 0xFFFF6B ) )
#define PORTC	( *( ( volatile unsigned char * ) 0xFFFF5B ) )
#define PCPCR	( *( ( volatile unsigned char * ) 0xFFFF72 ) )
#define PDDDR	( *( ( volatile unsigned char * ) 0xFFFEBC ) )
#define PDDR	( *( ( volatile unsigned char * ) 0xFFFF6C ) )
#define PORTD	( *( ( volatile unsigned char * ) 0xFFFF5C ) )
#define PDPCR	( *( ( volatile unsigned char * ) 0xFFFF73 ) )
#define PEDDR	( *( ( volatile unsigned char * ) 0xFFFEBD ) )
#define PEDR	( *( ( volatile unsigned char * ) 0xFFFF6D ) )
#define PORTE	( *( ( volatile unsigned char * ) 0xFFFF5D ) )
#define PEPCR	( *( ( volatile unsigned char * ) 0xFFFF74 ) )
#define PFDDR	( *( ( volatile unsigned char * ) 0xFFFEBE ) )
#define PFDR	( *( ( volatile unsigned char * ) 0xFFFF6E ) )
#define PORTF	( *( ( volatile unsigned char * ) 0xFFFF5E ) )
#define PFCR2	( *( ( volatile unsigned char * ) 0xFFFFAC ) )
#define SYSCR	( *( ( volatile unsigned char * ) 0xFFFF39 ) )
#define PGDDR	( *( ( volatile unsigned char * ) 0xFFFEBF ) )
#define PGDR	( *( ( volatile unsigned char * ) 0xFFFF6F ) )
#define PORTG	( *( ( volatile unsigned char * ) 0xFFFF5F ) )
#define PFCR2	( *( ( volatile unsigned char * ) 0xFFFFAC ) )


/* Definitions for TPU. */

#define TCR0	( *( ( volatile unsigned char * ) 0xFFFFD0 ) )
#define TMDR0	( *( ( volatile unsigned char * ) 0xFFFFD1 ) )
#define TIOR0H	( *( ( volatile unsigned char * ) 0xFFFFD2 ) )
#define TIOR0L	( *( ( volatile unsigned char * ) 0xFFFFD3 ) )
#define TIER0	( *( ( volatile unsigned char * ) 0xFFFFD4 ) )
#define TSR0	( *( ( volatile unsigned char * ) 0xFFFFD5 ) )
#define TCNT0	( *( ( volatile unsigned short * ) 0xFFFFD6 ) )
#define TGR0A	( *( ( volatile unsigned short * ) 0xFFFFD8 ) )
#define TGR0B	( *( ( volatile unsigned short * ) 0xFFFFDA ) )
#define TGR0C	( *( ( volatile unsigned short * ) 0xFFFFDC ) )
#define TGR0D	( *( ( volatile unsigned short * ) 0xFFFFDE ) )
#define TCR1	( *( ( volatile unsigned char * ) 0xFFFFE0 ) )
#define TMDR1	( *( ( volatile unsigned char * ) 0xFFFFE1 ) )
#define TIOR1	( *( ( volatile unsigned char * ) 0xFFFFE2 ) )
#define TIER1	( *( ( volatile unsigned char * ) 0xFFFFE4 ) )
#define TSR1	( *( ( volatile unsigned char * ) 0xFFFFE5 ) )
#define TCNT1	( *( ( volatile unsigned short * ) 0xFFFFE6 ) )
#define TGR1A	( *( ( volatile unsigned short * ) 0xFFFFE8 ) )
#define TGR1B	( *( ( volatile unsigned short * ) 0xFFFFEA ) )
#define TCR2	( *( ( volatile unsigned char * ) 0xFFFFF0 ) )
#define TMDR2	( *( ( volatile unsigned char * ) 0xFFFFF1 ) )
#define TIOR2	( *( ( volatile unsigned char * ) 0xFFFFF2 ) )
#define TIER2	( *( ( volatile unsigned char * ) 0xFFFFF4 ) )
#define TSR2	( *( ( volatile unsigned char * ) 0xFFFFF5 ) )
#define TCNT2	( *( ( volatile unsigned short * ) 0xFFFFF6 ) )
#define TGR2A	( *( ( volatile unsigned short * ) 0xFFFFF8 ) )
#define TGR2B	( *( ( volatile unsigned short * ) 0xFFFFFA ) )
#define TCR3	( *( ( volatile unsigned char * ) 0xFFFE80 ) )
#define TMDR3	( *( ( volatile unsigned char * ) 0xFFFE81 ) )
#define TIOR3H	( *( ( volatile unsigned char * ) 0xFFFE82 ) )
#define TIOR3L	( *( ( volatile unsigned char * ) 0xFFFE83 ) )
#define TIER3	( *( ( volatile unsigned char * ) 0xFFFE84 ) )
#define TSR3	( *( ( volatile unsigned char * ) 0xFFFE85 ) )
#define TCNT3	( *( ( volatile unsigned short * ) 0xFFFE86 ) )
#define TGR3A	( *( ( volatile unsigned short * ) 0xFFFE88 ) )
#define TGR3B	( *( ( volatile unsigned short * ) 0xFFFE8A ) )
#define TGR3C	( *( ( volatile unsigned short * ) 0xFFFE8C ) )
#define TGR3D	( *( ( volatile unsigned short * ) 0xFFFE8E ) )
#define TCR4	( *( ( volatile unsigned char * ) 0xFFFE90 ) )
#define TMDR4	( *( ( volatile unsigned char * ) 0xFFFE91 ) )
#define TIOR4	( *( ( volatile unsigned char * ) 0xFFFE92 ) )
#define TIER4	( *( ( volatile unsigned char * ) 0xFFFE94 ) )
#define TSR4	( *( ( volatile unsigned char * ) 0xFFFE95 ) )
#define TCNT4	( *( ( volatile unsigned short * ) 0xFFFE96 ) )
#define TGR4A	( *( ( volatile unsigned short * ) 0xFFFE98 ) )
#define TGR4B	( *( ( volatile unsigned short * ) 0xFFFE9A ) )
#define TCR5	( *( ( volatile unsigned char * ) 0xFFFEA0 ) )
#define TMDR5	( *( ( volatile unsigned char * ) 0xFFFEA1 ) )
#define TIOR5	( *( ( volatile unsigned char * ) 0xFFFEA2 ) )
#define TIER5	( *( ( volatile unsigned char * ) 0xFFFEA4 ) )
#define TSR5	( *( ( volatile unsigned char * ) 0xFFFEA5 ) )
#define TCNT5	( *( ( volatile unsigned short * ) 0xFFFEA6 ) )
#define TGR5A	( *( ( volatile unsigned short * ) 0xFFFEA8 ) )
#define TGR5B	( *( ( volatile unsigned short * ) 0xFFFEAA ) )
#define TSTR	( *( ( volatile unsigned char * ) 0xFFFFC0 ) )
#define TSYR	( *( ( volatile unsigned char * ) 0xFFFFC1 ) )


#define MSTPCR	( *( ( volatile unsigned short * ) 0xFFFF3C ) )
#define SCKCR	( *( ( volatile unsigned short * ) 0xFFFF3A ) )

/* Serial port. */

#define SMR0	( *( ( volatile unsigned char * ) 0xFFFF78 ) )
#define BRR0	( *( ( volatile unsigned char * ) 0xFFFF79 ) )
#define SCR0	( *( ( volatile unsigned char * ) 0xFFFF7A ) )
#define TDR0	( *( ( volatile unsigned char * ) 0xFFFF7B ) )
#define SSR0	( *( ( volatile unsigned char * ) 0xFFFF7C ) )
#define RDR0	( *( ( volatile unsigned char * ) 0xFFFF7D ) )
#define SCMR0	( *( ( volatile unsigned char * ) 0xFFFF7E ) )
#define SMR1	( *( ( volatile unsigned char * ) 0xFFFF80 ) )
#define BRR1	( *( ( volatile unsigned char * ) 0xFFFF81 ) )
#define SCR1	( *( ( volatile unsigned char * ) 0xFFFF82 ) )
#define TDR1	( *( ( volatile unsigned char * ) 0xFFFF83 ) )
#define SSR1	( *( ( volatile unsigned char * ) 0xFFFF84 ) )
#define RDR1	( *( ( volatile unsigned char * ) 0xFFFF85 ) )

#endif
