/* TA-LIB Copyright (c) 1999-2005, Mario Fortier
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither name of author nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* List of contributors:
 *
 *  Initial  Name/description
 *  -------------------------------------------------------------------
 *  AC       Angelo Ciceri
 *  MF       Mario Fortier
 *
 * Change history:
 *
 *  MMDDYY BY   Description
 *  -------------------------------------------------------------------
 *  032005 AC   Creation           
 *  041305 MF   Minor modification for a compiler warning
 */

/**** START GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
/* All code within this section is automatically
 * generated by gen_code. Any modification will be lost
 * next time gen_code is run.
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */    #using <mscorlib.dll>
/* Generated */    #include "Core.h"
/* Generated */    #define TA_INTERNAL_ERROR(Id) (TA_INTERNAL_ERROR)
/* Generated */    namespace TA { namespace Lib {
/* Generated */ #else
/* Generated */    #include <string.h>
/* Generated */    #include <math.h>
/* Generated */    #include "ta_func.h"
/* Generated */    #include "ta_trace.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_UTILITY_H
/* Generated */    #include "ta_utility.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_MEMORY_H
/* Generated */    #include "ta_memory.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #define TA_PREFIX(x) TA_##x
/* Generated */ #define INPUT_TYPE   double
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ int Core::CDLLADDERBOTTOM_Lookback( void )
/* Generated */ 
/* Generated */ #else
/* Generated */ int TA_CDLLADDERBOTTOM_Lookback( void )
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert lookback code here. */
    return TA_CANDLEAVGPERIOD(TA_ShadowVeryShort) + 4;
}

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/*
 * TA_CDLLADDERBOTTOM - Ladder Bottom
 * 
 * Input  = Open, High, Low, Close
 * Output = int
 * 
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ __value enum Core::TA_RetCode Core::CDLLADDERBOTTOM( int    startIdx,
/* Generated */                                                      int    endIdx,
/* Generated */                                                      double       inOpen __gc [],
/* Generated */                                                      double       inHigh __gc [],
/* Generated */                                                      double       inLow __gc [],
/* Generated */                                                      double       inClose __gc [],
/* Generated */                                                      [OutAttribute]Int32 *outBegIdx,
/* Generated */                                                      [OutAttribute]Int32 *outNbElement,
/* Generated */                                                      int           outInteger __gc [] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_CDLLADDERBOTTOM( int    startIdx,
/* Generated */                                int    endIdx,
/* Generated */                                const double inOpen[],
/* Generated */                                const double inHigh[],
/* Generated */                                const double inLow[],
/* Generated */                                const double inClose[],
/* Generated */                                int          *outBegIdx,
/* Generated */                                int          *outNbElement,
/* Generated */                                int           outInteger[] )
/* Generated */ #endif
/**** END GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
{
   /* Insert local variables here. */
    double ShadowVeryShortPeriodTotal;
    int i, outIdx, ShadowVeryShortTrailingIdx, lookbackTotal;

/**** START GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */    /* Validate the requested output range. */
/* Generated */    if( startIdx < 0 )
/* Generated */       return TA_OUT_OF_RANGE_START_INDEX;
/* Generated */    if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */       return TA_OUT_OF_RANGE_END_INDEX;
/* Generated */ 
/* Generated */    /* Validate the parameters. */
/* Generated */    /* Verify required price component. */
/* Generated */    if(!inOpen||!inHigh||!inLow||!inClose)
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */    if( outInteger == NULL )
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/

   /* Identify the minimum number of price bar needed
    * to calculate at least one output.
    */

   lookbackTotal = TA_CDLLADDERBOTTOM_Lookback();

   /* Move up the start index if there is not
    * enough initial data.
    */
   if( startIdx < lookbackTotal )
      startIdx = lookbackTotal;

   /* Make sure there is still something to evaluate. */
   if( startIdx > endIdx )
   {
      *outBegIdx = 0;
      *outNbElement = 0;
      return TA_SUCCESS;
   }

   /* Do the calculation using tight loops. */
   /* Add-up the initial period, except for the last value. */
   ShadowVeryShortPeriodTotal = 0;
   ShadowVeryShortTrailingIdx = startIdx - TA_CANDLEAVGPERIOD(TA_ShadowVeryShort);
   
   i = ShadowVeryShortTrailingIdx;
   while( i < startIdx ) {
        ShadowVeryShortPeriodTotal += TA_CANDLERANGE( TA_ShadowVeryShort, i-1 );
        i++;
   }
   i = startIdx;

   /* Proceed with the calculation for the requested range.
    * Must have:
    * - three black candlesticks with consecutively lower opens and closes
    * - fourth candle: black candle with an upper shadow (it's supposed to be not very short)
    * - fifth candle: white candle that opens above prior candle's body and closes above prior candle's high
    * The meaning of "very short" is specified with TA_SetCandleSettings
    * outInteger is positive (1 to 100): ladder bottom is always bullish; 
    * the user should consider that ladder bottom is significant when it appears in a downtrend, 
    * while this function does not consider it
    */
   outIdx = 0;
   do
   {
        if(                                                             
            TA_CANDLECOLOR(i-4) == -1 && TA_CANDLECOLOR(i-3) == -1 && TA_CANDLECOLOR(i-2) == -1 &&  // 3 black candlesticks
            inOpen[i-4] > inOpen[i-3] && inOpen[i-3] > inOpen[i-2] &&           // with consecutively lower opens
            inClose[i-4] > inClose[i-3] && inClose[i-3] > inClose[i-2] &&       // and closes
            TA_CANDLECOLOR(i-1) == -1 &&                                        // 4th: black with an upper shadow
            TA_UPPERSHADOW(i-1) > TA_CANDLEAVERAGE( TA_ShadowVeryShort, ShadowVeryShortPeriodTotal, i-1 ) &&
            TA_CANDLECOLOR(i) == 1 &&                                           // 5th: white
            inOpen[i] > inOpen[i-1] &&                                          // that opens above prior candle's body
            inClose[i] > inHigh[i-1]                                            // and closes above prior candle's high
          )
            outInteger[outIdx++] = 100;
        else
            outInteger[outIdx++] = 0;
        /* add the current range and subtract the first range: this is done after the pattern recognition 
         * when avgPeriod is not 0, that means "compare with the previous candles" (it excludes the current candle)
         */
        ShadowVeryShortPeriodTotal += TA_CANDLERANGE( TA_ShadowVeryShort, i-1 ) 
                                    - TA_CANDLERANGE( TA_ShadowVeryShort, ShadowVeryShortTrailingIdx-1 );
        i++; 
        ShadowVeryShortTrailingIdx++;
   } while( i <= endIdx );

   /* All done. Indicate the output limits and return. */
   *outNbElement = outIdx;
   *outBegIdx    = startIdx;

   return TA_SUCCESS;
}

/**** START GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #define  USE_SINGLE_PRECISION_INPUT
/* Generated */ #if !defined( _MANAGED )
/* Generated */    #undef   TA_PREFIX
/* Generated */    #define  TA_PREFIX(x) TA_S_##x
/* Generated */ #endif
/* Generated */ #undef   INPUT_TYPE
/* Generated */ #define  INPUT_TYPE float
/* Generated */ #if defined( _MANAGED )
/* Generated */ __value enum Core::TA_RetCode Core::CDLLADDERBOTTOM( int    startIdx,
/* Generated */                                                      int    endIdx,
/* Generated */                                                      float        inOpen __gc [],
/* Generated */                                                      float        inHigh __gc [],
/* Generated */                                                      float        inLow __gc [],
/* Generated */                                                      float        inClose __gc [],
/* Generated */                                                      [OutAttribute]Int32 *outBegIdx,
/* Generated */                                                      [OutAttribute]Int32 *outNbElement,
/* Generated */                                                      int           outInteger __gc [] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_S_CDLLADDERBOTTOM( int    startIdx,
/* Generated */                                  int    endIdx,
/* Generated */                                  const float  inOpen[],
/* Generated */                                  const float  inHigh[],
/* Generated */                                  const float  inLow[],
/* Generated */                                  const float  inClose[],
/* Generated */                                  int          *outBegIdx,
/* Generated */                                  int          *outNbElement,
/* Generated */                                  int           outInteger[] )
/* Generated */ #endif
/* Generated */ {
/* Generated */     double ShadowVeryShortPeriodTotal;
/* Generated */     int i, outIdx, ShadowVeryShortTrailingIdx, lookbackTotal;
/* Generated */  #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */     if( startIdx < 0 )
/* Generated */        return TA_OUT_OF_RANGE_START_INDEX;
/* Generated */     if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */        return TA_OUT_OF_RANGE_END_INDEX;
/* Generated */     if(!inOpen||!inHigh||!inLow||!inClose)
/* Generated */        return TA_BAD_PARAM;
/* Generated */     if( outInteger == NULL )
/* Generated */        return TA_BAD_PARAM;
/* Generated */  #endif 
/* Generated */    lookbackTotal = TA_CDLLADDERBOTTOM_Lookback();
/* Generated */    if( startIdx < lookbackTotal )
/* Generated */       startIdx = lookbackTotal;
/* Generated */    if( startIdx > endIdx )
/* Generated */    {
/* Generated */       *outBegIdx = 0;
/* Generated */       *outNbElement = 0;
/* Generated */       return TA_SUCCESS;
/* Generated */    }
/* Generated */    ShadowVeryShortPeriodTotal = 0;
/* Generated */    ShadowVeryShortTrailingIdx = startIdx - TA_CANDLEAVGPERIOD(TA_ShadowVeryShort);
/* Generated */    i = ShadowVeryShortTrailingIdx;
/* Generated */    while( i < startIdx ) {
/* Generated */         ShadowVeryShortPeriodTotal += TA_CANDLERANGE( TA_ShadowVeryShort, i-1 );
/* Generated */         i++;
/* Generated */    }
/* Generated */    i = startIdx;
/* Generated */    outIdx = 0;
/* Generated */    do
/* Generated */    {
/* Generated */         if(                                                             
/* Generated */             TA_CANDLECOLOR(i-4) == -1 && TA_CANDLECOLOR(i-3) == -1 && TA_CANDLECOLOR(i-2) == -1 &&  // 3 black candlesticks
/* Generated */             inOpen[i-4] > inOpen[i-3] && inOpen[i-3] > inOpen[i-2] &&           // with consecutively lower opens
/* Generated */             inClose[i-4] > inClose[i-3] && inClose[i-3] > inClose[i-2] &&       // and closes
/* Generated */             TA_CANDLECOLOR(i-1) == -1 &&                                        // 4th: black with an upper shadow
/* Generated */             TA_UPPERSHADOW(i-1) > TA_CANDLEAVERAGE( TA_ShadowVeryShort, ShadowVeryShortPeriodTotal, i-1 ) &&
/* Generated */             TA_CANDLECOLOR(i) == 1 &&                                           // 5th: white
/* Generated */             inOpen[i] > inOpen[i-1] &&                                          // that opens above prior candle's body
/* Generated */             inClose[i] > inHigh[i-1]                                            // and closes above prior candle's high
/* Generated */           )
/* Generated */             outInteger[outIdx++] = 100;
/* Generated */         else
/* Generated */             outInteger[outIdx++] = 0;
/* Generated */         ShadowVeryShortPeriodTotal += TA_CANDLERANGE( TA_ShadowVeryShort, i-1 ) 
/* Generated */                                     - TA_CANDLERANGE( TA_ShadowVeryShort, ShadowVeryShortTrailingIdx-1 );
/* Generated */         i++; 
/* Generated */         ShadowVeryShortTrailingIdx++;
/* Generated */    } while( i <= endIdx );
/* Generated */    *outNbElement = outIdx;
/* Generated */    *outBegIdx    = startIdx;
/* Generated */    return TA_SUCCESS;
/* Generated */ }
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ }} // Close namespace TA.Lib
/* Generated */ #endif
/**** END GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/

