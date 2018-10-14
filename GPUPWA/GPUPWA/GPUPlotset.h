/// \file GPUPlotset.h

#pragma once

#include <vector>
#include <TH1F.h>
#include <TH2F.h>
#include "TGraph.h"

using std::vector;

/// Class for storing and drawing sets of plots
/** IN GPUPWA, you generate vectors of plots (technically: std::vector<TH1F *>, where TH1F
is a root histogram class) using the GPUStreamScalar::Plot() function. These vectors, you
can then add to a GPUPlotset, which allows you to put your plots into a root file or
print them to a PostScript file.
**/
class GPUPlotset
{
public:
  /// Constructor, creating an empty set
  GPUPlotset(void);
  /// Destructor
  virtual ~GPUPlotset(void);
  /// Add a vector of plots
  void AddPlots(vector<TH1F *> plots){mHistos.push_back(plots);};
  /// Add a vector of 2D plots
  void AddPlots(vector<TH2F *> plots){m2DHistos.push_back(plots);};
  /// Add a graph
  void AddGraph(TGraph * graph){mGraphs.push_back(graph);};
  /// Format the individual plots
  /** The root default look for plots is ugly, so we make them nicer
      here. If you do not like how the plots look, write your own
      Format<Yourname> member function and call that one from the
      main program **/
  void Format();
  /// Write the plots to a root file
  void WriteRootfile(char * filename);
  /// Print the plots to a PostScript file
  /** In the current implementation, this will print a data-MC comparison
      of a particular projection in the top half of the page and the
      contributions from the individual waves and the interference terms in
      the bottom half, if these plots have been generated). The latter two arguments
      are ignored, but indicate that we might add more formatting options at a
      later stage */
  void WritePsfile(char * filename, int xplots=1, int yplots=1);
  /// Write the plots to individual files
  void WriteFiles(char * dirname, bool doeps = false, bool dopng = true);


protected:
  /// Storing the plots
  vector<vector<TH1F *> > mHistos;
  /// Storing the 2D plots
   vector<vector<TH2F *> > m2DHistos;
  /// Storing the graphs
  vector<TGraph *> mGraphs;

};
