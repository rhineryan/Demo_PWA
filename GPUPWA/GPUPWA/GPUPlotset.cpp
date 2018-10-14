#include "GPUPlotset.h"
#include "TPostScript.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLatex.h"

GPUPlotset::GPUPlotset(void)
{
}

GPUPlotset::~GPUPlotset(void)
{
}

void GPUPlotset::Format(){
	for(vector<vector <TH1F *> >::iterator it = mHistos.begin(); it < mHistos.end();++it){
		(*it)[0]->SetMarkerStyle(20);
		(*it)[1]->SetLineColor(2);
		if((*it)[0]->Integral() >= 0)
			(*it)[0]->SetMinimum(0);
		else
			(*it)[0]->SetMaximum(0);
		if((*it).size() > 2){
			for(int i = 2; i < (int)((*it).size()); i++){
				if((*it)[i]->Integral() >= 0)
					(*it)[i]->SetMinimum(0);
				else
					(*it)[i]->SetMaximum(0);
				(*it)[i]->SetLineStyle(i);
				(*it)[i]->SetLineColor(2);

			}
		}
	}

	for(vector<vector <TH2F *> >::iterator ite = m2DHistos.begin(); ite < m2DHistos.end();++ite){
		//(*ite)[0]->SetMarkerStyle(20);
		(*ite)[0]->SetMarkerColor(1);
		(*ite)[1]->SetMarkerColor(2);
		if((*ite)[0]->Integral() >= 0)
			(*ite)[0]->SetMinimum(0);
		else
			(*ite)[0]->SetMaximum(0);
		if((*ite).size() > 2){
			for(int i = 2; i < (int)((*ite).size()); i++){
				if((*ite)[i]->Integral() >= 0)
					(*ite)[i]->SetMinimum(0);
				else
					(*ite)[i]->SetMaximum(0);
				//(*it)[i]->SetLineStyle(i);
				(*ite)[i]->SetMarkerColor(1);

			}
		}
	}


	for(vector<TGraph *>::iterator it = mGraphs.begin(); it < mGraphs.end();++it){
		(*it)->SetMarkerStyle(20);
		(*it)->SetMarkerColor(2);
	}
}

void GPUPlotset::WriteRootfile(char * filename){
	TFile * f = new TFile(filename, "RECREATE");
	int i=0;
	for(vector<TGraph *>::iterator it = mGraphs.begin(); it < mGraphs.end();++it){
		char name[255];
		sprintf(name,"graph_%i",i);
		i++;
		(*it)->Write(name);
	}
	for(vector<vector <TH1F *> >::iterator it = mHistos.begin(); it < mHistos.end();++it){
		for(vector <TH1F *>::iterator it2 = it->begin(); it2 < it->end();it2++){
			(*it2)->Write();
		}
	}

	for(vector<vector <TH2F *> >::iterator it = m2DHistos.begin(); it < m2DHistos.end();++it){
			for(vector <TH2F *>::iterator it2 = it->begin(); it2 < it->end();it2++){
				(*it2)->Write();
			}
		}

	f->Close();
}

void GPUPlotset::WritePsfile(char * filename, int xplots, int yplots){
	TCanvas * c1 = new TCanvas("c1","PWA",600,800);

	TPostScript ps(filename, 111);
	//int plotsperpage = xplots*yplots;

	for(vector<TGraph * >::iterator it = mGraphs.begin(); it < mGraphs.end();++it){
		ps.NewPage();
		double xmin, ymin, xmax, ymax;
		(*it)->ComputeRange(xmin, ymin, xmax, ymax);
		TH1F * histo = new TH1F("Graph","Graph",10,xmin,xmax);
		histo->SetMaximum(ymax + (ymax-ymin)*0.1);
		histo->SetMinimum(ymin - (ymax-ymin)*0.1);
		histo->Draw();
		(*it)->Draw("P");
		c1->Update();
	}

	//ps.NewPage();
	//int index =0;
	for(vector<vector <TH1F *> >::iterator it = mHistos.begin(); it < mHistos.end();++it){
		ps.NewPage();
		c1->Clear();
		c1->Divide(1, 2);
		c1->cd(1);
		if((*it)[0]->GetMaximum() > (*it)[1]->GetMaximum()){
			(*it)[0]->Draw("E0");
			(*it)[1]->Draw("Same");
		} else {
			(*it)[1]->Draw();
			(*it)[0]->Draw("E0same");
		}

		TVirtualPad * pad = c1->cd(2);
		int nwaves = (int)it->size() -2;
		if(nwaves <=2){
			pad->Divide(nwaves,1);
		} else if(nwaves == 3){
			pad->Divide(nwaves,1);
		} else if(nwaves == 4){
			pad->Divide(2,2);
		}else{
			int rows = (nwaves+3)/4;
			pad->Divide(int((float)nwaves/(float)rows+0.5), rows);
		}
		for(int i=0; i < nwaves; i++){
			pad->cd(i+1);
			(*it)[i+2]->Draw();
			double num = (*it)[i+2]->Integral();
			char text[255];
			sprintf(text, "%0.1f events in wave", num);
			double histocenter = ((*it)[i+2]->GetBinCenter(1) + (*it)[i+2]->GetBinCenter((*it)[i+2]->GetNbinsX()-2))/2.0;
			TLatex *tex;
			if((*it)[i+2]->Integral() >= 0)
				tex = new TLatex(histocenter,(*it)[i+2]->GetMaximum()*0.1, text);
			else
				tex = new TLatex(histocenter,(*it)[i+2]->GetMinimum()*0.1, text);
			tex->SetTextFont(42);
			tex->SetTextSize(0.05);
			tex->SetTextAlign(21);
			tex->Draw();
		}
		//if(index%plotsperpage == 0){
		c1->Update();

		//	c1->cd();
		//	c1->Clear();
		//	c1->Divide(xplots, yplots);
		//}
	}

	//ps.NewPage();
	//int index =0;
	for(vector<vector <TH2F *> >::iterator it = m2DHistos.begin(); it < m2DHistos.end();++it){
		ps.NewPage();
		c1->Clear();
		c1->Divide(1, 2);
		TVirtualPad * toppad = c1->cd(1);
		toppad->Divide(2,1);
		toppad->cd(1);
			(*it)[0]->Draw();
		toppad->cd(2);
			(*it)[1]->Draw();


		TVirtualPad * pad = c1->cd(2);
		int nwaves = (int)it->size() -2;
		if(nwaves <=2){
			pad->Divide(nwaves,1);
		} else if(nwaves == 3){
			pad->Divide(nwaves,1);
		} else if(nwaves == 4){
			pad->Divide(2,2);
		}else{
			int rows = (nwaves+3)/4;
			pad->Divide(int((float)nwaves/(float)rows+0.5), rows);
		}
		for(int i=0; i < nwaves; i++){
			pad->cd(i+1);
			(*it)[i+2]->Draw();
			/*	double num = (*it)[i+2]->Integral();
			char text[255];
			sprintf(text, "%0.1f events in wave", num);
			double histocenter = ((*it)[i+2]->GetBinCenter(1) + (*it)[i+2]->GetBinCenter((*it)[i+2]->GetNbinsX()-2))/2.0;
			TLatex *tex;
			if((*it)[i+2]->Integral() >= 0)
				tex = new TLatex(histocenter,(*it)[i+2]->GetMaximum()*0.1, text);
			else
				tex = new TLatex(histocenter,(*it)[i+2]->GetMinimum()*0.1, text);
			tex->SetTextFont(42);
			tex->SetTextSize(0.05);
			tex->SetTextAlign(21);
			tex->Draw();*/
		}

		c1->Update();

			//	c1->cd();
			//	c1->Clear();
			//	c1->Divide(xplots, yplots);
			//}
	}


	ps.Close();
}

void GPUPlotset::WriteFiles(char * dirname, bool doeps, bool dopng){
	TCanvas * c1 = new TCanvas("c1","PWA",800,600);

	int ngraph = 0;
	char filename[512];
	for(vector<TGraph * >::iterator it = mGraphs.begin(); it < mGraphs.end();++it){
		double xmin, ymin, xmax, ymax;
		(*it)->ComputeRange(xmin, ymin, xmax, ymax);
		TH1F * histo = new TH1F("Graphbg","Graphbg",10,xmin,xmax);
		histo->SetMaximum(ymax + (ymax-ymin)*0.1);
		histo->SetMinimum(ymin - (ymax-ymin)*0.1);
		histo->Draw();
		(*it)->Draw("P");
		c1->Update();
		if(doeps){
			sprintf(filename,"%s/Graph_%i.eps", dirname, ngraph);
			c1->SaveAs(filename);
		}
		if(dopng){
			sprintf(filename,"%s/Graph_%i.png", dirname, ngraph);
			c1->SaveAs(filename);
		}
		ngraph++;
	}

	//int index =0;
	for(vector<vector <TH1F *> >::iterator it = mHistos.begin(); it < mHistos.end();++it){
		c1->Clear();
		if((*it)[0]->GetMaximum() > (*it)[1]->GetMaximum()){
			(*it)[0]->Draw("E0");
			(*it)[1]->Draw("Same");
		} else {
			(*it)[1]->Draw();
			(*it)[0]->Draw("E0same");
		}
		c1->Update();
		if(doeps){
			sprintf(filename,"%s/%s_Fit.eps", dirname, (*it)[0]->GetName());
			c1->SaveAs(filename);
		}
		if(dopng){
			sprintf(filename,"%s/%s_Fit.png", dirname, (*it)[0]->GetName());
			c1->SaveAs(filename);
		}

		c1->Clear();
		int nwaves = (int)it->size() -2;
		if(nwaves <=2){
			c1->Divide(nwaves,1);
		} else if(nwaves == 3){
			c1->Divide(nwaves,1);
		} else if(nwaves == 4){
			c1->Divide(2,2);
		}else{
			int rows = (nwaves+3)/4;
			c1->Divide(int((float)nwaves/(float)rows+0.5), rows);
		}
		for(int i=0; i < nwaves; i++){
			c1->cd(i+1);
			(*it)[i+2]->Draw();
			double num = (*it)[i+2]->Integral();
			char text[255];
			sprintf(text, "%0.1f events in wave", num);
			double histocenter = ((*it)[i+2]->GetBinCenter(1) + (*it)[i+2]->GetBinCenter((*it)[i+2]->GetNbinsX()-2))/2.0;
			TLatex *tex;
			if((*it)[i+2]->Integral() >= 0)
				tex = new TLatex(histocenter,(*it)[i+2]->GetMaximum()*0.1, text);
			else
				tex = new TLatex(histocenter,(*it)[i+2]->GetMinimum()*0.1, text);
			tex->SetTextFont(42);
			tex->SetTextSize(0.05);
			tex->SetTextAlign(21);
			tex->Draw();
		}
		c1->Update();
		if(doeps){
			sprintf(filename,"%s/%s_Waves.eps", dirname, (*it)[1]->GetName());
			c1->SaveAs(filename);
		}
		if(dopng){
			sprintf(filename,"%s/%s_Waves.png", dirname, (*it)[1]->GetName());
			c1->SaveAs(filename);
		}

		c1->Clear();
		if((*it)[0]->GetMaximum() > (*it)[1]->GetMaximum()){
			(*it)[0]->Draw("E0");
			(*it)[1]->Draw("Same");
		} else {
			(*it)[1]->Draw();
			(*it)[0]->Draw("E0same");
		}
		for(int i=0; i < nwaves; i++){
			if((*it)[i+2]->Integral() >= 0)
				(*it)[i+2]->Draw("same");
		}
		if(doeps){
			sprintf(filename,"%s/%s_Composite.eps", dirname, (*it)[1]->GetName());
			c1->SaveAs(filename);
		}
		if(dopng){
			sprintf(filename,"%s/%s_Composite.png", dirname, (*it)[1]->GetName());
			c1->SaveAs(filename);
		}

	}

	for(vector<vector <TH2F *> >::iterator it = m2DHistos.begin(); it < m2DHistos.end();++it){
			c1->Clear();
			c1->Divide(2,1);
			c1->cd(1);
			(*it)[0]->Draw();
			c1->cd(2);
			(*it)[1]->Draw();
			c1->Update();
			if(doeps){
				sprintf(filename,"%s/%s_Fit.eps", dirname, (*it)[0]->GetName());
				c1->SaveAs(filename);
			}
			if(dopng){
				sprintf(filename,"%s/%s_Fit.png", dirname, (*it)[0]->GetName());
				c1->SaveAs(filename);
			}

			c1->Clear();
			int nwaves = (int)it->size() -2;
			if(nwaves <=2){
				c1->Divide(nwaves,1);
			} else if(nwaves == 3){
				c1->Divide(nwaves,1);
			} else if(nwaves == 4){
				c1->Divide(2,2);
			}else{
				int rows = (nwaves+3)/4;
				c1->Divide(int((float)nwaves/(float)rows+0.5), rows);
			}
			for(int i=0; i < nwaves; i++){
				c1->cd(i+1);
				(*it)[i+2]->Draw();
			/*	double num = (*it)[i+2]->Integral();
				char text[255];
				sprintf(text, "%0.1f events in wave", num);
				double histocenter = ((*it)[i+2]->GetBinCenter(1) + (*it)[i+2]->GetBinCenter((*it)[i+2]->GetNbinsX()-2))/2.0;
				TLatex *tex;
				if((*it)[i+2]->Integral() >= 0)
					tex = new TLatex(histocenter,(*it)[i+2]->GetMaximum()*0.1, text);
				else
					tex = new TLatex(histocenter,(*it)[i+2]->GetMinimum()*0.1, text);
				tex->SetTextFont(42);
				tex->SetTextSize(0.05);
				tex->SetTextAlign(21);
				tex->Draw();*/
			}
			c1->Update();
			if(doeps){
				sprintf(filename,"%s/%s_Waves.eps", dirname, (*it)[1]->GetName());
				c1->SaveAs(filename);
			}
			if(dopng){
				sprintf(filename,"%s/%s_Waves.png", dirname, (*it)[1]->GetName());
				c1->SaveAs(filename);
			}


		}



}

