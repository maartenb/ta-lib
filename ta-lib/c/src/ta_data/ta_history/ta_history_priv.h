#ifndef TA_HISTORY_PRIV_H
#define TA_HISTORY_PRIV_H

/* Contains declarations/prototypes private to the TA_History module. */

#ifndef TA_STRING_H
   #include "ta_string.h"
#endif

#ifndef TA_COMMON_H
   #include "ta_common.h"
#endif

#ifndef TA_LIST_H
   #include "ta_list.h"
#endif

#ifndef TA_HISTORY_H
   #include "ta_history.h"
#endif

typedef struct
{
   TA_Real *open;
   TA_Real *high;
   TA_Real *low;
   TA_Real *close;
   TA_Integer *volume;
   TA_Integer *openInterest;
   TA_Timestamp *timestamp;

   TA_Integer nbBars;
   TA_Period  period;

   TA_Field   fieldProvided;
} TA_DataBlock;

typedef struct
{
  /* All the data allocated while the processing of building
   * the TA_History will be refer one way or the other from here.
   * (except for the data possibly internally allocated by the
   * driver of course). This will allow to easily clean-up everything
   * when something wrong happen.
   */
  TA_List *listOfSupportForDataSource; /* List of TA_SupportForDataSource. */

  TA_List *listOfMergeOp;  /* List of TA_MergeOp */
  unsigned int nbPriceBar; /* Final number of price bar. */

  /* When TA_ALL is requested, we keep track of the set of common
   * field provided among all the data source.
   */
  TA_Field commonFieldProvided;

  /* Indicates if an error has been detected at ANY point while building
   * the TA_History.
   */
  TA_RetCode retCode;

} TA_BuilderSupport;


typedef struct
{
   /* Describe a 'copy' operation that must be performed when merging.
    * Many instances of this structure will usually exist to complete
    * a merging.
    */
   TA_DataBlock *srcDataBlock;
   unsigned int srcIndexForCopy;
   unsigned int nbElementToCopy;
} TA_MergeOp;

/* Structure to store split/value adjustments.
 *
 * A split adjustement affects both the price and
 * the volume in the same proportion.
 *
 * A value  adjustment affects only the price. Examples
 * are dividend, disbursment etc...
 */
typedef struct
{
   TA_Timestamp timestamp;
   double factor;
} TA_SplitAdjust;

typedef struct
{
   TA_Timestamp timestamp;
   double amount;
} TA_ValueAdjust;


/* This structure is the private version for the TA_ParamForAddData type. */
typedef struct
{
  /* An instance of this structure will exist for each data source involve
   * when a TA_HistoryAlloc call is done.
   */

  /* Parameters needed to be passed to the data soruce driver. */
  TA_BuilderSupport   *parent;
  TA_DataSourceHandle *sourceHandle;
  TA_CategoryHandle   *categoryHandle;
  TA_SymbolHandle     *symbolHandle;
  TA_Period            period;
  const TA_Timestamp  *start;
  const TA_Timestamp  *end;
  TA_Field             fieldToAlloc;

  /* Setting this variable to one will force the driver to stop
   * processing as soon as possible the addition of data.
   * Basically, it is a way for the caller of the driver to say... I got
   * enough data from you!
   */
  volatile unsigned int enoughValidDataProvided;

  /* This variable will get set to one when the driver return from
   * the GetHistoryData function.
   */
  volatile unsigned int finishIndication;

  /* Indicates the fields provided. Can be different than
   * fieldToAlloc if the driver:
   * 1) provides more field than requested.
   * 2) When fieldToAlloc is TA_ALL.
   *
   * Of course, fieldProvided cannot be TA_ALL, it must be specific
   * about WHICH fields are provided by this driver.
   *
   * It is assumed (and verified) that all data block (in listOfDataBlock)
   * provides the same fields.
   */
  TA_Field fieldProvided;

  /* The driver have the liberty to provide the data in a timeframe
   * smaller than requested by 'period' (see above).
   * It is verified that all data added by the same driver (in listOfDataBlock)
   * have the same period though.
   */
  TA_Period periodProvided;

  /* The latest return code of the GetHistoryData function. */
  volatile TA_RetCode retCode;

  TA_List *listOfDataBlock; /* Lists of TA_DataBlock. */


  /* We keep track of the extremes in the listOfDataBlock. */
  const TA_Timestamp *lowestTimestamp;
  const TA_Timestamp *highestTimestamp;

  /* The following values are reset everytime the data
   * source driver calls TA_GetInfoFromAddedData
   */
  unsigned int barAddedSinceLastCall; /* boolean */
  const TA_Timestamp *lowestTimestampAddedSinceLastCall;
  const TA_Timestamp *highestTimestampAddedSinceLastCall; 

  /* Provides information about which feature the
   * datasource can support.
   */
  TA_DataSourceParameters supportedParameter;

  /* Parameter that were used when this data
   * source was added.
   */
  const TA_AddDataSourceParamPriv *addDataSourceParamPriv;

  /* List of TA_SplitAdjust structures. */
  TA_List *listOfSplitAdjust;

  /* List of TA_ValueAdjust structures. */
  TA_List *listOfValueAdjust;

  /* The following variables are used only while doing the merging with
   * the other data sources. They allow to keep track of the next
   * price bar to be processed for this particular data source.
   */
  unsigned int allDataConsumed;
  unsigned int curIndex;
  const TA_Timestamp *curTimestamp;
  const TA_Timestamp *curLastTimestamp;
  TA_DataBlock       *curDataBlock;

  /* Indicates if that data source has data part of the
   * final data returned to the caller of TA_HistoryAlloc.
   */
  unsigned int contributingDataSource;

} TA_SupportForDataSource;

/********** Prototype for function in ta_period.c *********/

/* Will make all list of datablock use the same period. The datablock
 * with the longuest period will determine the period.
 *
 * Example: if a data source provides the data in 15 minutes increment
 *          and another in daily price bar, all data block will be normalize
 *          to daily period.
 */
TA_RetCode TA_PeriodNormalize( TA_BuilderSupport *builderSupport );


/* Allocate data in a different timeframe from
 * an existing history.
 *
 * When the parameter doAllocateNew is != 0, the history 
 * is transformed and the "Allocate new" pointers
 * will be all NULL.
 *
 * When the parameter doAllocateNew == 0, the "history"
 * is left untouch, and all the new data are returned
 * through the "Allocate new" pointers. TA_Free must be 
 * called on these pointers when not needed anymore.
 *
 * In both case, you will need to free "history" as usual.
 */
TA_RetCode TA_PeriodTransform( TA_History *history,       /* The original history. */
                               TA_Period newPeriod,       /* The new desired period. */
                               TA_HistoryFlag flags,
                               int doAllocateNew,         /* When true, following ptrs are used. */
                               TA_Integer *nbBars,        /* Return the number of price bar */
                               TA_Timestamp **timestamp,  /* Allocate new timestamp. */
                               TA_Real **open,            /* Allocate new open. */
                               TA_Real **high,            /* Allocate new high. */
                               TA_Real **low,             /* Allocate new low. */
                               TA_Real **close,           /* Allocate new close. */
                               TA_Integer **volume,       /* Allocate new volume. */
                               TA_Integer **openInterest  /* Allocate new openInterest. */ );

#endif
