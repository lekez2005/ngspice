/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
Modified: 2000 AlansFixes
**********/

#ifndef VDMOS
#define VDMOS

#include "ngspice/ifsim.h"
#include "ngspice/cktdefs.h"
#include "ngspice/gendefs.h"
#include "ngspice/complex.h"
#include "ngspice/noisedef.h"

/* declarations for level 1 MOSFETs */

/* information needed for each instance */

typedef struct sVDMOSinstance {

    struct GENinstance gen;

#define VDMOSmodPtr(inst) ((struct sVDMOSmodel *)((inst)->gen.GENmodPtr))
#define VDMOSnextInstance(inst) ((struct sVDMOSinstance *)((inst)->gen.GENnextInstance))
#define VDMOSname gen.GENname
#define VDMOSstates gen.GENstate

    const int VDMOSdNode;  /* number of the gate node of the mosfet */
    const int VDMOSgNode;  /* number of the gate node of the mosfet */
    const int VDMOSsNode;  /* number of the source node of the mosfet */
    const int VDMOSbNode;  /* number of the bulk node of the mosfet */
    int VDMOSdNodePrime; /* number of the internal drain node of the mosfet */
    int VDMOSsNodePrime; /* number of the internal source node of the mosfet */
    int VDMOSgNodePrime; /* number of the internal gate node of the mosfet */

    double VDMOSm;   /* parallel device multiplier */

    double VDMOSl;   /* the length of the channel region */
    double VDMOSw;   /* the width of the channel region */
    double VDMOSsourceConductance;   /*conductance of source(or 0):set in setup*/
    double VDMOSdrainConductance;    /*conductance of drain(or 0):set in setup*/
    double VDMOSgateConductance;    /*conductance of gate(or 0):set in setup*/
    double VDMOStemp;    /* operating temperature of this instance */
    double VDMOSdtemp;   /* operating temperature of the instance relative to circuit temperature*/

    double VDMOStTransconductance;   /* temperature corrected transconductance*/
    double VDMOStSurfMob;            /* temperature corrected surface mobility */
    double VDMOStPhi;                /* temperature corrected Phi */
    double VDMOStVto;                /* temperature corrected Vto */
    double VDMOStSatCur;             /* temperature corrected saturation Cur. */
    double VDMOStSatCurDens; /* temperature corrected saturation Cur. density*/
    double VDMOStCbd;                /* temperature corrected B-D Capacitance */
    double VDMOStCbs;                /* temperature corrected B-S Capacitance */
    double VDMOStCj;         /* temperature corrected Bulk bottom Capacitance */
    double VDMOStBulkPot;    /* temperature corrected Bulk potential */
    double VDMOStDepCap;     /* temperature adjusted transition point in */
                            /* the cureve matching Fc * Vj */
    double VDMOStVbi;        /* temperature adjusted Vbi */

    double VDMOSicVBS;   /* initial condition B-S voltage */
    double VDMOSicVDS;   /* initial condition D-S voltage */
    double VDMOSicVGS;   /* initial condition G-S voltage */
    double VDMOSvon;
    double VDMOSvdsat;
    double VDMOSsourceVcrit; /* Vcrit for pos. vds */
    double VDMOSdrainVcrit;  /* Vcrit for pos. vds */
    double VDMOScd;
    double VDMOScbs;
    double VDMOScbd;
    double VDMOSgmbs;
    double VDMOSgm;
    double VDMOSgds;
    double VDMOSgbd;
    double VDMOSgbs;
    double VDMOScapbd;
    double VDMOScapbs;
    double VDMOSCbd;
    double VDMOSCbdsw;
    double VDMOSCbs;
    double VDMOSCbssw;
    double VDMOSf2d;
    double VDMOSf3d;
    double VDMOSf4d;
    double VDMOSf2s;
    double VDMOSf3s;
    double VDMOSf4s;

/*
 * naming convention:
 * x = vgs
 * y = vbs
 * z = vds
 * cdr = cdrain
 */

#define	VDMOSNDCOEFFS	30

#ifndef NODISTO
	double VDMOSdCoeffs[VDMOSNDCOEFFS];
#else /* NODISTO */
	double *VDMOSdCoeffs;
#endif /* NODISTO */

#ifndef CONFIG

#define	capbs2		VDMOSdCoeffs[0]
#define	capbs3		VDMOSdCoeffs[1]
#define	capbd2		VDMOSdCoeffs[2]
#define	capbd3		VDMOSdCoeffs[3]
#define	gbs2		VDMOSdCoeffs[4]
#define	gbs3		VDMOSdCoeffs[5]
#define	gbd2		VDMOSdCoeffs[6]
#define	gbd3		VDMOSdCoeffs[7]
#define	capgb2		VDMOSdCoeffs[8]
#define	capgb3		VDMOSdCoeffs[9]
#define	cdr_x2		VDMOSdCoeffs[10]
#define	cdr_y2		VDMOSdCoeffs[11]
#define	cdr_z2		VDMOSdCoeffs[12]
#define	cdr_xy		VDMOSdCoeffs[13]
#define	cdr_yz		VDMOSdCoeffs[14]
#define	cdr_xz		VDMOSdCoeffs[15]
#define	cdr_x3		VDMOSdCoeffs[16]
#define	cdr_y3		VDMOSdCoeffs[17]
#define	cdr_z3		VDMOSdCoeffs[18]
#define	cdr_x2z		VDMOSdCoeffs[19]
#define	cdr_x2y		VDMOSdCoeffs[20]
#define	cdr_y2z		VDMOSdCoeffs[21]
#define	cdr_xy2		VDMOSdCoeffs[22]
#define	cdr_xz2		VDMOSdCoeffs[23]
#define	cdr_yz2		VDMOSdCoeffs[24]
#define	cdr_xyz		VDMOSdCoeffs[25]
#define	capgs2		VDMOSdCoeffs[26]
#define	capgs3		VDMOSdCoeffs[27]
#define	capgd2		VDMOSdCoeffs[28]
#define	capgd3		VDMOSdCoeffs[29]

#endif

#define VDMOSRDNOIZ	0
#define VDMOSRSNOIZ   1
#define VDMOSIDNOIZ       2
#define VDMOSFLNOIZ 3
#define VDMOSTOTNOIZ    4

#define VDMOSNSRCS     5     /* the number of VDMOSFET noise sources*/

#ifndef NONOISE
    double VDMOSnVar[NSTATVARS][VDMOSNSRCS];
#else /* NONOISE */
	double **VDMOSnVar;
#endif /* NONOISE */

    int VDMOSmode;       /* device mode : 1 = normal, -1 = inverse */


    unsigned VDMOSoff:1;  /* non-zero to indicate device is off for dc analysis*/
    unsigned VDMOStempGiven :1;  /* instance temperature specified */
    unsigned VDMOSdtempGiven :1;  /* instance delta temperature specified */
    unsigned VDMOSmGiven :1;
    unsigned VDMOSlGiven :1;
    unsigned VDMOSwGiven :1;
    unsigned VDMOSdNodePrimeSet  :1;
    unsigned VDMOSsNodePrimeSet  :1;
    unsigned VDMOSicVBSGiven :1;
    unsigned VDMOSicVDSGiven :1;
    unsigned VDMOSicVGSGiven :1;
    unsigned VDMOSvonGiven   :1;
    unsigned VDMOSvdsatGiven :1;
    unsigned VDMOSmodeGiven  :1;


    double *VDMOSDdPtr;      /* pointer to sparse matrix element at
                                     * (Drain node,drain node) */
    double *VDMOSGgPtr;      /* pointer to sparse matrix element at
                                     * (gate node,gate node) */
    double *VDMOSSsPtr;      /* pointer to sparse matrix element at
                                     * (source node,source node) */
    double *VDMOSBbPtr;      /* pointer to sparse matrix element at
                                     * (bulk node,bulk node) */
    double *VDMOSDPdpPtr;    /* pointer to sparse matrix element at
                                     * (drain prime node,drain prime node) */
    double *VDMOSSPspPtr;    /* pointer to sparse matrix element at
                                     * (source prime node,source prime node) */
    double *VDMOSDdpPtr;     /* pointer to sparse matrix element at
                                     * (drain node,drain prime node) */
    double *VDMOSGbPtr;      /* pointer to sparse matrix element at
                                     * (gate node,bulk node) */
    double *VDMOSGdpPtr;     /* pointer to sparse matrix element at
                                     * (gate node,drain prime node) */
    double *VDMOSGspPtr;     /* pointer to sparse matrix element at
                                     * (gate node,source prime node) */
    double *VDMOSSspPtr;     /* pointer to sparse matrix element at
                                     * (source node,source prime node) */
    double *VDMOSBdpPtr;     /* pointer to sparse matrix element at
                                     * (bulk node,drain prime node) */
    double *VDMOSBspPtr;     /* pointer to sparse matrix element at
                                     * (bulk node,source prime node) */
    double *VDMOSDPspPtr;    /* pointer to sparse matrix element at
                                     * (drain prime node,source prime node) */
    double *VDMOSDPdPtr;     /* pointer to sparse matrix element at
                                     * (drain prime node,drain node) */
    double *VDMOSBgPtr;      /* pointer to sparse matrix element at
                                     * (bulk node,gate node) */
    double *VDMOSDPgPtr;     /* pointer to sparse matrix element at
                                     * (drain prime node,gate node) */

    double *VDMOSSPgPtr;     /* pointer to sparse matrix element at
                                     * (source prime node,gate node) */
    double *VDMOSSPsPtr;     /* pointer to sparse matrix element at
                                     * (source prime node,source node) */
    double *VDMOSDPbPtr;     /* pointer to sparse matrix element at
                                     * (drain prime node,bulk node) */
    double *VDMOSSPbPtr;     /* pointer to sparse matrix element at
                                     * (source prime node,bulk node) */
    double *VDMOSSPdpPtr;    /* pointer to sparse matrix element at
                                     * (source prime node,drain prime node) */
    /* VDMOS */
    double *VDMOSGPgpPtr;    /* pointer to sparse matrix element at
                             * (gate prime node, gate prime node) */
    double *VDMOSGPbPtr;    /* pointer to sparse matrix element at
                             * (gate prime node, bulk node) */
    double *VDMOSGPdpPtr;    /* pointer to sparse matrix element at
                             * (gate prime node, drain prime node) */
    double *VDMOSGPspPtr;    /* pointer to sparse matrix element at
                             * (gate prime node, source prime node) */
    double *VDMOSBgpPtr;    /* pointer to sparse matrix element at
                             * (bulk node, gate prime node) */
    double *VDMOSDPgpPtr;    /* pointer to sparse matrix element at
                             * (drain prime node, gate prime node) */
    double *VDMOSSPgpPtr;    /* pointer to sparse matrix element at
                             * (source prime node, gate prime node) */
    double *VDMOSGgpPtr;    /* pointer to sparse matrix element at
                             * (gate node, gate prime node) */
    double *VDMOSGPgPtr;    /* pointer to sparse matrix element at
                             * (gate prime node, gate node) */

    int  VDMOSsenParmNo;   /* parameter # for sensitivity use;
            set equal to 0  if  neither length
            nor width of the mosfet is a design
            parameter */
    unsigned VDMOSsens_l :1;   /* field which indicates whether  
            length of the mosfet is a design
            parameter or not */
    unsigned VDMOSsens_w :1;   /* field which indicates whether  
            width of the mosfet is a design
            parameter or not */
    unsigned VDMOSsenPertFlag :1; /* indictes whether the the 
            parameter of the particular instance is 
            to be perturbed */
    double VDMOScgs;
    double VDMOScgd;
    double VDMOScgb;
    double *VDMOSsens;

#define VDMOSsenCgs VDMOSsens /* contains pertured values of cgs */
#define VDMOSsenCgd VDMOSsens + 6 /* contains perturbed values of cgd*/
#define VDMOSsenCgb VDMOSsens + 12 /* contains perturbed values of cgb*/
#define VDMOSsenCbd VDMOSsens + 18 /* contains perturbed values of cbd*/
#define VDMOSsenCbs VDMOSsens + 24 /* contains perturbed values of cbs*/
#define VDMOSsenGds VDMOSsens + 30 /* contains perturbed values of gds*/
#define VDMOSsenGbs VDMOSsens + 36 /* contains perturbed values of gbs*/
#define VDMOSsenGbd VDMOSsens + 42 /* contains perturbed values of gbd*/
#define VDMOSsenGm VDMOSsens + 48 /* contains perturbed values of gm*/
#define VDMOSsenGmbs VDMOSsens + 54 /* contains perturbed values of gmbs*/
#define VDMOSdphigs_dl VDMOSsens + 60
#define VDMOSdphigd_dl VDMOSsens + 61
#define VDMOSdphigb_dl VDMOSsens + 62
#define VDMOSdphibs_dl VDMOSsens + 63
#define VDMOSdphibd_dl VDMOSsens + 64
#define VDMOSdphigs_dw VDMOSsens + 65
#define VDMOSdphigd_dw VDMOSsens + 66
#define VDMOSdphigb_dw VDMOSsens + 67
#define VDMOSdphibs_dw VDMOSsens + 68
#define VDMOSdphibd_dw VDMOSsens + 69

} VDMOSinstance ;

#define VDMOSvbd VDMOSstates+ 0   /* bulk-drain voltage */
#define VDMOSvbs VDMOSstates+ 1   /* bulk-source voltage */
#define VDMOSvgs VDMOSstates+ 2   /* gate-source voltage */
#define VDMOSvds VDMOSstates+ 3   /* drain-source voltage */

#define VDMOScapgs VDMOSstates+4  /* gate-source capacitor value */
#define VDMOSqgs VDMOSstates+ 5   /* gate-source capacitor charge */
#define VDMOScqgs VDMOSstates+ 6  /* gate-source capacitor current */

#define VDMOScapgd VDMOSstates+ 7 /* gate-drain capacitor value */
#define VDMOSqgd VDMOSstates+ 8   /* gate-drain capacitor charge */
#define VDMOScqgd VDMOSstates+ 9  /* gate-drain capacitor current */

#define VDMOScapgb VDMOSstates+10 /* gate-bulk capacitor value */
#define VDMOSqgb VDMOSstates+ 11  /* gate-bulk capacitor charge */
#define VDMOScqgb VDMOSstates+ 12 /* gate-bulk capacitor current */

#define VDMOSqbd VDMOSstates+ 13  /* bulk-drain capacitor charge */
#define VDMOScqbd VDMOSstates+ 14 /* bulk-drain capacitor current */

#define VDMOSqbs VDMOSstates+ 15  /* bulk-source capacitor charge */
#define VDMOScqbs VDMOSstates+ 16 /* bulk-source capacitor current */

#define VDMOSnumStates 17

#define VDMOSsensxpgs VDMOSstates+17 /* charge sensitivities and 
          their derivatives.  +18 for the derivatives:
          pointer to the beginning of the array */
#define VDMOSsensxpgd  VDMOSstates+19
#define VDMOSsensxpgb  VDMOSstates+21
#define VDMOSsensxpbs  VDMOSstates+23
#define VDMOSsensxpbd  VDMOSstates+25

#define VDMOSnumSenStates 10


/* per model data */

    /* NOTE:  parameters marked 'input - use xxxx' are paramters for
     * which a temperature correction is applied in VDMOStemp, thus
     * the VDMOSxxxx value in the per-instance structure should be used
     * instead in all calculations 
     */


typedef struct sVDMOSmodel {       /* model structure for a resistor */

    struct GENmodel gen;

#define VDMOSmodType gen.GENmodType
#define VDMOSnextModel(inst) ((struct sVDMOSmodel *)((inst)->gen.GENnextModel))
#define VDMOSinstances(inst) ((VDMOSinstance *)((inst)->gen.GENinstances))
#define VDMOSmodName gen.GENmodName

    int VDMOStype;       /* device type : 1 = nmos,  -1 = pmos */
    double VDMOStnom;        /* temperature at which parameters measured */
    double VDMOSjctSatCurDensity;    /* input - use tSatCurDens */
    double VDMOSjctSatCur;   /* input - use tSatCur */
    double VDMOSdrainResistance;
    double VDMOSsourceResistance;
    double VDMOSgateResistance;
    double VDMOSsheetResistance;
    double VDMOStransconductance;    /* input - use tTransconductance */
    double VDMOSgateSourceOverlapCapFactor;
    double VDMOSgateDrainOverlapCapFactor;
    double VDMOSgateBulkOverlapCapFactor;
    double VDMOSoxideCapFactor;
    double VDMOSvt0; /* input - use tVto */
    double VDMOScapBD;   /* input - use tCbd */
    double VDMOScapBS;   /* input - use tCbs */
    double VDMOSbulkCapFactor;   /* input - use tCj */
    double VDMOSbulkJctPotential;    /* input - use tBulkPot */
    double VDMOSbulkJctBotGradingCoeff;
    double VDMOSfwdCapDepCoeff;
    double VDMOSphi; /* input - use tPhi */
    double VDMOSgamma;
    double VDMOSlambda;
    double VDMOSsubstrateDoping;
    int VDMOSgateType;
    double VDMOSsurfaceStateDensity;
    double VDMOSoxideThickness;
    double VDMOSsurfaceMobility; /* input - use tSurfMob */
    double VDMOSfNcoef;
    double VDMOSfNexp;
    double VDMOScgdmin;
    double VDMOScgdmax;
    double VDMOSa;
    double VDMOScgs;

    unsigned VDMOStypeGiven  :1;
    unsigned VDMOSjctSatCurDensityGiven  :1;
    unsigned VDMOSjctSatCurGiven :1;
    unsigned VDMOSdrainResistanceGiven   :1;
    unsigned VDMOSsourceResistanceGiven  :1;
    unsigned VDMOSgateResistanceGiven    :1;
    unsigned VDMOStransconductanceGiven  :1;
    unsigned VDMOSgateSourceOverlapCapFactorGiven    :1;
    unsigned VDMOSgateDrainOverlapCapFactorGiven :1;
    unsigned VDMOSgateBulkOverlapCapFactorGiven  :1;
    unsigned VDMOSvt0Given   :1;
    unsigned VDMOScapBDGiven :1;
    unsigned VDMOScapBSGiven :1;
    unsigned VDMOSbulkCapFactorGiven :1;
    unsigned VDMOSbulkJctPotentialGiven  :1;
    unsigned VDMOSbulkJctBotGradingCoeffGiven    :1;
    unsigned VDMOSfwdCapDepCoeffGiven    :1;
    unsigned VDMOSphiGiven   :1;
    unsigned VDMOSgammaGiven :1;
    unsigned VDMOSlambdaGiven    :1;
    unsigned VDMOSsubstrateDopingGiven   :1;
    unsigned VDMOSgateTypeGiven  :1;
    unsigned VDMOSsurfaceStateDensityGiven   :1;
    unsigned VDMOSoxideThicknessGiven    :1;
    unsigned VDMOSsurfaceMobilityGiven   :1;
    unsigned VDMOStnomGiven  :1;
    unsigned VDMOSfNcoefGiven  :1;
    unsigned VDMOSfNexpGiven   :1;

    unsigned VDMOScgdminGiven   :1;
    unsigned VDMOScgdmaxGiven   :1;
    unsigned VDMOScgsGiven   :1;
    unsigned VDMOSaGiven   :1;

} VDMOSmodel;

#ifndef NMOS
#define NMOS 1
#define PMOS -1
#endif /*NMOS*/

/* device parameters */
#define VDMOS_W 1
#define VDMOS_L 2
#define VDMOS_OFF 9
#define VDMOS_IC 10
#define VDMOS_IC_VBS 11
#define VDMOS_IC_VDS 12
#define VDMOS_IC_VGS 13
#define VDMOS_W_SENS 14
#define VDMOS_L_SENS 15
#define VDMOS_CB 16
#define VDMOS_CG 17
#define VDMOS_CS 18
#define VDMOS_POWER 19
#define VDMOS_TEMP 20
#define VDMOS_M 21
#define VDMOS_DTEMP 22
/* model paramerers */
#define VDMOS_MOD_VTO 101
#define VDMOS_MOD_KP 102
#define VDMOS_MOD_PHI 104
#define VDMOS_MOD_LAMBDA 105
#define VDMOS_MOD_RD 106
#define VDMOS_MOD_RS 107
#define VDMOS_MOD_IS 110
#define VDMOS_MOD_VJ 111
#define VDMOS_MOD_CJ 115
#define VDMOS_MOD_MJ 116
#define VDMOS_MOD_JS 119
#define VDMOS_MOD_TOX 120
#define VDMOS_MOD_U0 123
#define VDMOS_MOD_FC 124
#define VDMOS_MOD_NSUB 125
#define VDMOS_MOD_TPG 126
#define VDMOS_MOD_NSS 127
#define VDMOS_MOD_NMOS 128
#define VDMOS_MOD_PMOS 129
#define VDMOS_MOD_TNOM 130
#define VDMOS_MOD_KF 131
#define VDMOS_MOD_AF 132
#define VDMOS_MOD_TYPE 133
#define VDMOS_MOD_DMOS 134

#define VDMOS_MOD_CGDMIN 150
#define VDMOS_MOD_CGDMAX 151
#define VDMOS_MOD_A 152
#define VDMOS_MOD_CGS 153
#define VDMOS_MOD_RG 154

/* device questions */
#define VDMOS_CGS                201
#define VDMOS_CGD                202
#define VDMOS_DNODE              203
#define VDMOS_GNODE              204
#define VDMOS_SNODE              205
#define VDMOS_BNODE              206
#define VDMOS_DNODEPRIME         207
#define VDMOS_SNODEPRIME         208
#define VDMOS_SOURCECONDUCT      209
#define VDMOS_DRAINCONDUCT       210
#define VDMOS_VON                211
#define VDMOS_VDSAT              212
#define VDMOS_SOURCEVCRIT        213
#define VDMOS_DRAINVCRIT         214
#define VDMOS_CD                 215
#define VDMOS_CBS                216
#define VDMOS_CBD                217
#define VDMOS_GMBS               218
#define VDMOS_GM                 219
#define VDMOS_GDS                220
#define VDMOS_GBD                221
#define VDMOS_GBS                222
#define VDMOS_CAPBD              223
#define VDMOS_CAPBS              224
#define VDMOS_CAPZEROBIASBD      225
#define VDMOS_CAPZEROBIASBDSW    226
#define VDMOS_CAPZEROBIASBS      227
#define VDMOS_CAPZEROBIASBSSW    228
#define VDMOS_VBD                229
#define VDMOS_VBS                230
#define VDMOS_VGS                231
#define VDMOS_VDS                232
#define VDMOS_CAPGS              233
#define VDMOS_QGS                234
#define VDMOS_CQGS               235
#define VDMOS_CAPGD              236
#define VDMOS_QGD                237
#define VDMOS_CQGD               238
#define VDMOS_CAPGB              239
#define VDMOS_QGB                240
#define VDMOS_CQGB               241
#define VDMOS_QBD                242
#define VDMOS_CQBD               243
#define VDMOS_QBS                244
#define VDMOS_CQBS               245
#define VDMOS_L_SENS_REAL               246
#define VDMOS_L_SENS_IMAG               247
#define VDMOS_L_SENS_MAG                248 
#define VDMOS_L_SENS_PH                 249 
#define VDMOS_L_SENS_CPLX               250
#define VDMOS_W_SENS_REAL               251
#define VDMOS_W_SENS_IMAG               252
#define VDMOS_W_SENS_MAG                253 
#define VDMOS_W_SENS_PH                 254 
#define VDMOS_W_SENS_CPLX               255
#define VDMOS_L_SENS_DC                 256
#define VDMOS_W_SENS_DC                 257
#define VDMOS_SOURCERESIST      258
#define VDMOS_DRAINRESIST       259

/* model questions */

#include "vdmosext.h"

#endif /*VDMOS*/

