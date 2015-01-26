#include <Rcpp.h>

# maxGapMinRun algorithm
# 1-line documentation TBA.

using namespace Rcpp;
IntegerVector segStarts(seg_starts);
IntegerVector segEnds(seg_ends);
NumericVector segScore(seg_xpr);
IntegerVector segCtr(seg_ctr);

IntegerVector probeStarts(probe_start);
IntegerVector probeLen(probe_len);
NumericVector probeVal(smoothed);

IntegerVector maxGap(max_gap);
IntegerVector minRun(min_run);
IntegerVector posThresh(pos_thresh);

Rcpp::Rcout << "Params: maxGap = " << maxGap[0] << " ; minRun = " << minRun[0] << " ; thre

int seg_ctr=0;
int EMPTY_VAL=0;
int currseg_start=EMPTY_VAL;
int ssize = probeStarts.size();
// lookahead approach
double currseg_score=0;
int currseg_count=0;
for (int k=0; k < (ssize-1); k++) {
  if (probeVal[k] >= posThresh[0]) { // T

        if (probeVal[k+1] < posThresh[0]) { // TF -> end seg.
            if (currseg_start==EMPTY_VAL) currseg_start=probeStarts[k];
            segStarts[seg_ctr]=currseg_start; // TODO - ADD MINRUN part. Add score.
            segEnds[seg_ctr]=probeStarts[k] + (probeLen[0]-1);
      segScore[seg_ctr] = currseg_score/(double)currseg_count;
            // i.e. do not count segments shorter than minRun, otherwise overwrite this on
            if (((segEnds[seg_ctr]-segStarts[seg_ctr])+1) > minRun[0]) seg_ctr++;

            currseg_start=EMPTY_VAL; currseg_score=0; currseg_count=0;

        } else { // TT - next probe exceeds threshold too
            if (((probeStarts[k+1]-probeStarts[k])+1) <= maxGap[0]) { //TTT -> extend seg
                if (currseg_start==EMPTY_VAL) currseg_start=probeStarts[k];
        currseg_score+=probeVal[k+1]; currseg_count++;
            } else { //TTF -> end old seg. start new seg.
                if (currseg_start==EMPTY_VAL) currseg_start=probeStarts[k];
                segStarts[seg_ctr]=currseg_start;
                segEnds[seg_ctr]=probeStarts[k]+(probeLen[0]-1);
        segScore[seg_ctr]=currseg_score/(double)currseg_count;

                if (((segEnds[seg_ctr]-segStarts[seg_ctr])+1) > minRun[0]) seg_ctr++;
                currseg_start=probeStarts[k+1];
        currseg_score=probeVal[k+1]; currseg_count++;
            }
        }
    }
};
if (probeVal[ssize-1] > posThresh[0]) {
    if (currseg_start != EMPTY_VAL) { //close last segment
    segStarts[seg_ctr]=currseg_start; // TODO - ADD MINRUN part. Add score.
    segEnds[seg_ctr]=probeStarts[ssize-1]+ (probeLen[0]-1);
  segScore[seg_ctr]=currseg_score;
    if (((segEnds[seg_ctr]-segStarts[seg_ctr])+1) > minRun[0]) seg_ctr++;
    }
    else if (probeLen[0]>minRun[0]) { // this probe counts as its own segment
    segStarts[seg_ctr] = probeStarts[ssize-1];
    segEnds[seg_ctr] = probeStarts[ssize-1] + (probeLen[0]-1);
  segScore[seg_ctr]  = probeVal[ssize-1];
    seg_ctr++;
    }
}
segCtr[0]=seg_ctr;
