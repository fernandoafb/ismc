#include "sbsat.h"
#include "sbsat_solver.h"
#include "solver.h"

//MINMAX State

void initMINMAXStateType() {
   arrStatesTypeSize[FN_MINMAX] = sizeof(MINMAXStateEntry);
   arrSetVisitedState[FN_MINMAX] = SetVisitedMINMAXState;
   arrApplyInferenceToState[FN_MINMAX] = ApplyInferenceToMINMAX;
   arrPrintStateEntry[FN_MINMAX] = PrintMINMAXStateEntry;
   arrPrintStateEntry_dot[FN_MINMAX] = NULL;
   arrFreeStateEntry[FN_MINMAX] = FreeMINMAXStateEntry;
   arrCalculateStateHeuristic[FN_MINMAX] = CalculateMINMAXLSGBHeuristic;
   arrSetStateHeuristicScore[FN_MINMAX] = LSGBMINMAXStateSetHeurScore;
   arrGetStateHeuristicScore[FN_MINMAX] = LSGBMINMAXStateGetHeurScore;
}

void PrintMINMAXStateEntry(void *pState) {
   MINMAXStateEntry *pMINMAXState = (MINMAXStateEntry *)pState;
	d9_printf2("MM %d <= ", pMINMAXState->nMin);
	for(int x = 0; x < pMINMAXState->nSize; x++)
	  d9_printf2("%d ", pMINMAXState->pnTransitionVars[x]);
	d9_printf2("<= %d ", pMINMAXState->nMax);
	d9_printf2("Size=%d\n", pMINMAXState->nSize);
}

void FreeMINMAXStateEntry(void *pState) {
   MINMAXStateEntry *pMINMAXState = (MINMAXStateEntry *)pState;
	ite_free((void **)&pMINMAXState->pnTransitionVars);
   if(pMINMAXState->pMINMAXStateBDD != NULL) {
      pMINMAXState->pMINMAXStateBDD->pState = NULL;
   }
}

//MINMAX Counter State

void initMINMAXCounterStateType() {
   arrStatesTypeSize[FN_MINMAX_COUNTER] = sizeof(MINMAXCounterStateEntry);
   arrSetVisitedState[FN_MINMAX_COUNTER] = SetVisitedMINMAXCounterState;
   arrApplyInferenceToState[FN_MINMAX_COUNTER] = ApplyInferenceToMINMAXCounter;
   arrPrintStateEntry[FN_MINMAX_COUNTER] = PrintMINMAXCounterStateEntry;
   arrPrintStateEntry_dot[FN_MINMAX_COUNTER] = NULL;
   arrFreeStateEntry[FN_MINMAX_COUNTER] = FreeMINMAXCounterStateEntry;
   arrCalculateStateHeuristic[FN_MINMAX_COUNTER] = CalculateMINMAXCounterLSGBHeuristic;
   arrSetStateHeuristicScore[FN_MINMAX_COUNTER] = LSGBMINMAXCounterStateSetHeurScore;
   arrGetStateHeuristicScore[FN_MINMAX_COUNTER] = LSGBMINMAXCounterStateGetHeurScore;
}

void PrintMINMAXCounterStateEntry(void *pState) {
   MINMAXCounterStateEntry *pMINMAXCounterState = (MINMAXCounterStateEntry *)pState;
	d9_printf5("MC Next=%p Head=%p VarsLeft=%d NumTrue=%d\n", 
              (void *)pMINMAXCounterState->pTransition,
              (void *)pMINMAXCounterState->pMINMAXState, 
              pMINMAXCounterState->nVarsLeft, 
              pMINMAXCounterState->nNumTrue);
}

void FreeMINMAXCounterStateEntry(void *pState) {
		
}
