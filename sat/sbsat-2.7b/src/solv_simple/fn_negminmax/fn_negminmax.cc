#include "sbsat.h"
#include "sbsat_solver.h"
#include "solver.h"

//NEGMINMAX State

void initNEGMINMAXStateType() {
   arrStatesTypeSize[FN_NEGMINMAX] = sizeof(NEGMINMAXStateEntry);
   arrSetVisitedState[FN_NEGMINMAX] = SetVisitedNEGMINMAXState;
   arrApplyInferenceToState[FN_NEGMINMAX] = ApplyInferenceToNEGMINMAX;
   arrPrintStateEntry[FN_NEGMINMAX] = PrintNEGMINMAXStateEntry;
	arrPrintStateEntry_dot[FN_NEGMINMAX] = NULL;
   arrFreeStateEntry[FN_NEGMINMAX] = FreeNEGMINMAXStateEntry;
   arrCalculateStateHeuristic[FN_NEGMINMAX] = CalculateNEGMINMAXLSGBHeuristic;
   arrSetStateHeuristicScore[FN_NEGMINMAX] = LSGBNEGMINMAXStateSetHeurScore;
   arrGetStateHeuristicScore[FN_NEGMINMAX] = LSGBNEGMINMAXStateGetHeurScore;
}

void PrintNEGMINMAXStateEntry(void *pState) {
   NEGMINMAXStateEntry *pNEGMINMAXState = (NEGMINMAXStateEntry *)pState;
	d9_printf2("NMM %d <= ", pNEGMINMAXState->nMin);
	for(int x = 0; x < pNEGMINMAXState->nSize; x++)
	  d9_printf2("%d ", pNEGMINMAXState->pnTransitionVars[x]);
	d9_printf2("<= %d ", pNEGMINMAXState->nMax);
	d9_printf2("Size=%d\n", pNEGMINMAXState->nSize);
}

void FreeNEGMINMAXStateEntry(void *pState) {
   NEGMINMAXStateEntry *pNEGMINMAXState = (NEGMINMAXStateEntry *)pState;
	ite_free((void **)&pNEGMINMAXState->pnTransitionVars);
   if(pNEGMINMAXState->pNEGMINMAXStateBDD != NULL) {
      pNEGMINMAXState->pNEGMINMAXStateBDD->pState = NULL;
   }           
}

//NEGMINMAX Counter State

void initNEGMINMAXCounterStateType() {
   arrStatesTypeSize[FN_NEGMINMAX_COUNTER] = sizeof(NEGMINMAXCounterStateEntry);
   arrSetVisitedState[FN_NEGMINMAX_COUNTER] = SetVisitedNEGMINMAXCounterState;
   arrApplyInferenceToState[FN_NEGMINMAX_COUNTER] = ApplyInferenceToNEGMINMAXCounter;
   arrPrintStateEntry[FN_NEGMINMAX_COUNTER] = PrintNEGMINMAXCounterStateEntry;
   arrPrintStateEntry_dot[FN_NEGMINMAX_COUNTER] = NULL;
   arrFreeStateEntry[FN_NEGMINMAX_COUNTER] = FreeNEGMINMAXCounterStateEntry;
   arrCalculateStateHeuristic[FN_NEGMINMAX_COUNTER] = CalculateNEGMINMAXCounterLSGBHeuristic;
   arrSetStateHeuristicScore[FN_NEGMINMAX_COUNTER] = LSGBNEGMINMAXCounterStateSetHeurScore;
   arrGetStateHeuristicScore[FN_NEGMINMAX_COUNTER] = LSGBNEGMINMAXCounterStateGetHeurScore;
}

void PrintNEGMINMAXCounterStateEntry(void *pState) {
   NEGMINMAXCounterStateEntry *pNEGMINMAXCounterState = (NEGMINMAXCounterStateEntry *)pState;
	d9_printf5("NMC Next=%p Head=%p VarsLeft=%d NumTrue=%d\n", 
              (void *)pNEGMINMAXCounterState->pTransition,
              (void *)pNEGMINMAXCounterState->pNEGMINMAXState,
              pNEGMINMAXCounterState->nVarsLeft,
              pNEGMINMAXCounterState->nNumTrue);
}

void FreeNEGMINMAXCounterStateEntry(void *pState) {
		
}
