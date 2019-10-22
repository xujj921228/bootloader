#ifndef __SPI_H__
#define __SPI_H__

#include "derivative.h" /* include peripheral declarations */

#define     MAX_SPI_NO              2
#define SPI_BIT_RATE    200000     /* ~500kbps */
/******************************************************************************
*
*//*! @addtogroup spi_setting_type
* @{
*******************************************************************************/
/*!
 * @brief SPI setting type.
 *
 */
typedef struct
{
    uint32_t bIntEn                               : 1; /*!< 1: Interrupt Enable, 0: Interrupt disable */
    uint32_t bModuleEn                            : 1; /*!< 1: SPI module Enable, 0: SPI module disable */
    uint32_t bTxIntEn                             : 1; /*!< 1: Tx Interrupt Enable, 0: Tx Interrupt disable */
    uint32_t bMasterMode                          : 1; /*!< 1: Master mode, 0: Slave mode */
    uint32_t bClkPolarityLow                      : 1; /*!< 1: Active-low SPI clock, 0: Active-HIgh SPI clock */
    uint32_t bClkPhase1                           : 1; /*!< Set clock phase */
    uint32_t bMasterAutoDriveSS                   : 1; /*!< Slave select output enable */
    uint32_t bShiftLSBFirst                       : 1; /*!< 1: LSB first, 0: MSB first */
    uint32_t bMatchIntEn                          : 1; /*!< 1: Match interrupt Enable, 0: Match interrupt disable */
    uint32_t bModeFaultEn                         : 1; /*!< Master mode-fault function enable */
    uint32_t bBidirectionModeEn                   : 1; /*!< Bidirectional mode output enable */
    uint32_t bPinAsOuput                          : 1; /*!< enables bidirectional pin configurations */
    uint32_t bStopInWaitMode                      : 1; /*!< SPI stop in wait mode */
    uint32_t bRsvd                                : 19;
} SPI_SettingType;
/*! @} End of spi_setting_type                                            */

/******************************************************************************
*
*//*! @addtogroup spi_config_type
* @{
*******************************************************************************/
/*!
 * @brief SPI configuration type.
 *
 */
typedef struct 
{
    SPI_SettingType       sSettings;              /*!< SPI settings */
    uint32_t              u32BitRate;             /*!< set baud rate */
    uint32_t              u32BusClkHz;            /*!< input bus clock */
} SPI_ConfigType;                              /*!< SPI configuration structure */
/*! @} End of spi_config_type                                            */

/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* inline function
******************************************************************************/
/******************************************************************************
*
*//*! @addtogroup spi_api_list
* @{
*******************************************************************************/

/*****************************************************************************//*!
   *
   * @brief enable SPI module.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/

 static inline void SPI_Enable(void)
{
	SPI0_C1 |= SPI_C1_SPE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief disable SPI module.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *  
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/

 static inline void SPI_Disable(void)
{
	 SPI0_C1 &= ~SPI_C1_SPE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief enable SPI interrupt.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/

 static inline void SPI_IntEnable(void)
{
	 SPI0_C1 |= SPI_C1_SPIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief disable SPI interrupt.
   *        
   * @param[in]  pSPI   point to SPI module type.  
   *
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
 static inline void SPI_IntDisable(void)
{
	 SPI0_C1 &= ~SPI_C1_SPIE_MASK;
}

/*******************************************************************
*************Instruction set of the rain light sensor***************
********************************************************************/

 #define NRM    0xE400      //Normal Running Mode
 #define SD     0xC300      //Start Diagnositcs
 #define CR     0xF000      //Chip Reset
 #define RO     0xC300      //Start Read-Out
 #define SM     0xD0FF      //Start Measure All Parameters
 #define RSLP   0xE100      //75308
 #define CSLP   0xA300
/******************************* SM command ************************/
/********************* 1101 R2R1R0T  M6M5M4M3 M2M1M0P **************/ 
 #define R2     0x0800      //offset_opamp_aa_filter, every twice processing can cancel the effect
 #define R1     0x0400      //offset_opamp_sclp_filter,every twice processing can cancel the effect 
 #define R0     0x0200      //offset_opamp_adc_buffer,every twice processing can cancel the effect
 #define T      0x0100      //replaced the light pulses by internal current pulses during the rain measurements
 
 #define TMP    0x80        
 #define AMBLT  0x40
 #define DCLT   0x20
 #define LEDA   0x10
 #define LEDB   0x08
 #define RMCHA  0x04
 #define RMCHB  0x02


/*******************************************************************
**********************User Register Address*************************
********************************************************************/
#define addr_SetAna   0x0
#define addr_SetAH    0x1
#define addr_SetAL    0x2
#define addr_SetBH    0x3
#define addr_SetBL    0x4
#define addr_SetPF    0x5
#define addr_Err      0x6
#define addr_Rst      0x7
#define addr_DCComp1  0x8
#define addr_DCComp2  0x9
#define addr_GainBuf  0xA
#define addr_Calib1   0xB
#define addr_Calib2   0xC
#define addr_EnChan   0xD
#define addr_Tamb     0xE


/*******************************************************************
**************************User Register ****************************
********************************************************************/


/*******************************************************************
**********************Parameter Address*************************
********************************************************************/
#define Tdem          	0x01
#define Unity_Gain    	0x02
#define GAIN_ADJ_AA_A 	0x03
#define GAIN_ADJ_AA_B 	0x04
#define BW_ADJ_AA_A	    0x05
#define BW_ADJ_AA_B   	0x06
#define BW_SEL_LP_A	    0x07
#define BW_SEL_LP_B   	0x08
#define NP	          	0x09
#define RF	          	0x0a
#define DACA	        	0x0b
#define DACB	        	0x0c
#define GAIN_BUF      	0x0d
#define EN_DCCOMP       0x0e
#define DC_COMP_IC1     0x0f
#define DC_COMP_IC2     0x10
#define DC_COMP_IC3     0x11
#define DC_COMP_IC4     0x12
#define DC_COMP_IC5     0x13
#define Tdc             0x14



/*******************************************************************
**********************Parameter Address*************************
********************************************************************/

/*******************************************************************
**********************Meanure Channel*************************
********************************************************************/
#define Temp      	0x80	//1000_0000
#define PDA       	0x10	//0001_0000
#define PDB    	  	0x08	//0000_1000
#define PDC    	  	0x04	//0000_0100
#define PDD    	  	0x02	//0000_0010
#define PDE	      	0x01	//0000_0001
/*******************************************************************
**********************Meanure Channel*************************
********************************************************************/


struct MLX75308_Parameter 
{
  uint8 SetAna;		//Tdem[3:0],LEDDRV_HG,Tdc_pulse1,Tdc_pulse0,Unity_Gain
  uint8 SetAH;		//DACA[7:0]
  uint8 SetAL;		//GAIN_ADJ_AA_A[2:0],BW_ADJ_AA_A[2:0],BW_SEL_LP_A[1:0]
  uint8 SetBH;		//DACB[7:0]
  uint8 SetBL;		//GAIN_ADJ_AA_B[2:0],BW_ADJ_AA_B[2:0],BW_SEL_LP_B[1:0]
  uint8 GainBuf;
};

 

struct MLX75308_Frame 
{
  uint8  StateFlag;
  uint8  CtrlByte1;
  uint16 data_field[10];
  uint8  CRC;
};

//MLX75308 Measure Parameter
struct MLX75308_Mnrval
{
  uint16 Temperature;
  uint16 Amb_C;
  uint16 Amb_D;        //Brightness_FW
  uint16 Amb_E;        //Brightness_IR
  uint16 DC_bre_A;
  uint16 DC_bre_B;
  uint16 IR_A;
  uint16 IR_B;
  uint16 DC_aft_A;
  uint16 DC_aft_B;  
};

 
extern struct MLX75308_Mnrval     Mnrval;
extern struct MLX75308_Frame       MLX75308_RxFrame;


extern uint8 SPI_Rd_Reg(uint8 Addr);
extern uint8 SPI_Wr_Reg(uint8 Data, uint8 Addr);
extern uint8 SPI_Wr_Reg(uint8 Data, uint8 Addr);
extern uint8 SPI_Wr_Cmd(uint16 Cmd);                        
extern void MLX75308_Meansure(uint8 Mnsr_chan); 
extern uint8 MLX75308_SetPara(uint8 Para_Name,uint8 Set_val);

/******************************************************************************
* Global functions
******************************************************************************/
extern void SPI_Enable(void);
extern void SPI_Disable(void);

extern uint8 SPI_COM(uint8 ucData);
extern void SPI_Init(void);
                       
#endif
