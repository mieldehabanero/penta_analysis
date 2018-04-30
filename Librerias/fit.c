//
//  fit.c
//  
//
//  Created by Ricardo Zamora on 30/4/18.
//

#include "fit.h"

void fit_double_gauss(std::string data_path, std::string ntuple_name, std::string variable_name, std::string variable_title, std::string variable_description, std::vector<float> variable_range, std::vector<float> mean_range, std::vector<float> sigma1_range, std::vector<float> sigma2_range, std::vector<float> sigma_fraction, std::vector<vector<float>> poly_range, std::vector<float> background_fraction, unsigned int bin_number){
	//Nombre y Título del modelo
	std::string fit_name = "double_gaussian";
	std::string fit_title = "Double Gaussian";
	
	//Lee los datos filtrados del archivo
	TFile *file = new TFile(data_path.data(), "READ");
	TTree *ntuple = nullptr;
	file->GetObject(ntuple_name.data(), ntuple);
	
	//Variable independiente
	RooRealVar mass(variable_name.data(), variable_description.data(), variable_range[0], variable_range[1]) ;
	
	//Parámetros para la señal (doble Gaussiana)
	RooRealVar mean("mean", "mean of gaussian", mean_range[0], mean_range[1], mean_range[2]);
	RooRealVar sigma1("sigma1", "width of gaussian", sigma1_range[0], sigma1_range[1], sigma1_range[2]);
	RooRealVar sigma2("sigma2", "width of gaussian", sigma2_range[0], sigma2_range[1], sigma2_range[2]);
	RooGaussian gaussian_1("gaussian_1", "Signal component 1", mass, mean, sigma1);
	RooGaussian gaussian_2("gaussian_2", "Signal component 2", mass, mean, sigma2);
	
	//Parámetros para el ruido (Pol(1))
	RooRealVar a1("a1", "coef de orden 1", poly_range[0][0], poly_range[0][1], poly_range[0][2]);
	RooPolynomial poly("poly", "bkg PDF", mass, RooArgSet(a1));
	
	//Se crea el data set
	RooDataSet *data = new RooDataSet("data", "Datos del 2012 filtrados", ntuple, mass);
	
	//Suma las PDFs de la señal
	RooRealVar gaussian_1_frac("gaussian_1_frac","Fraction of Gaussian 1 in signal", sigma_fraction[0], sigma_fraction[1], sigma_fraction[2]);
	RooAddPdf double_gaussian(fit_name.data(),"Signal",RooArgList(gaussian_1, gaussian_2), gaussian_1_frac) ;
	
	//Suma señal con el background
	RooRealVar bkgfrac("bkgfrac","Fraction of background", background_fraction[0], background_fraction[1], background_fraction[2]);
	RooAddPdf  model("model","g1+g2+a", RooArgList(poly, double_gaussian), bkgfrac);
	
	//Se hace el ajuste
	RooFitResult* result = model.fitTo(*data, Save(kTRUE), NumCPU(4));
	
	//Se dibujan los datos, el ajuste, y sus componentes
	RooPlot* frame_fit = mass.frame(Title(variable_description.data()), Bins(bin_number));
	data->plotOn(frame_fit);
	model.plotOn(frame_fit, LineColor(kBlue), NumCPU(4));
	RooHist* hpull = frame_fit->pullHist();
	model.plotOn(frame_fit, Components(poly),LineStyle(kDashed), NumCPU(4));
	model.plotOn(frame_fit, Components(RooArgSet(gaussian_1, gaussian_2)), LineStyle(kDotted), LineColor(kRed), NumCPU(4));
	
	//Crea el pull para el ajuste
//	RooHist* hpull = frame_fit->pullHist();
	std::string frame_hpull_title = variable_description + " Pull Distribution";
	RooPlot* frame_hpull = mass.frame(Title(frame_hpull_title.data()));
	frame_hpull->addPlotable(hpull,"PY");
	
	//Se generan los nombres y títulos de los canvas
	std::string canvas_name = variable_name + "_" + fit_name;
	std::string canvas_title = variable_title + " " + fit_title + " Fit";
	std::string canvas_hpull_name = variable_name + "_" + fit_name + "_hpull";
	std::string canvas_hpull_title = canvas_title + " Pull Distribution";
	
	//Se crean los canvas y se dibuja todo
	TCanvas* canvas_fit = new TCanvas(canvas_name.data(), canvas_title.data(), 600, 600) ;
	canvas_fit->cd();
	frame_fit->GetYaxis()->SetTitleOffset(1.6);
	gPad->SetTicks(1, 1);
	frame_fit->Draw();
	
	TCanvas* canvas_hpull = new TCanvas(canvas_hpull_name.data(), canvas_hpull_title.data(), 600, 600);
	canvas_hpull->cd();
	frame_hpull->GetYaxis()->SetTitleOffset(1.6);
	gPad->SetTicks(1, 1);
	frame_hpull->Draw();
	
	//Se guardan los histogramas en archivos
	std::string path_folder = "Resultados/Histogramas/Fit/";
	std::string path_fit = path_folder + canvas_name + ".png";
	std::string path_hpull = path_folder + canvas_hpull_name + ".png";
	canvas_fit->Print(path_fit.data());
	canvas_hpull->Print(path_hpull.data());
	
	//Print structure of composite p.d.f.
	model.Print("t") ;
}

void fit_breit_wigner(std::string data_path, std::string ntuple_name, std::string variable_name, std::string variable_description, std::vector<float> variable_range, std::vector<float> mean_range, std::vector<float> gamma_range, std::vector<vector<float>> d0_params, std::vector<float> background_fraction, unsigned int bin_number){
	//Lee los datos filtrados del archivo
	TFile* file = new TFile(data_path.data(), "READ");
	TTree* ntuple = nullptr;
	file->GetObject(ntuple_name.data(), ntuple);
	
	//Observable
	RooRealVar mass(variable_name.data(), variable_description.data(), variable_range[0], variable_range[1]) ;
	
	//Background DØ
	RooRealVar m_thr("m_thr", "m_thr", d0_params[0][0]);
	RooRealVar c1("c1", "c1", d0_params[1][0], d0_params[1][1], d0_params[1][2]);
	RooRealVar c2("c2", "c2", d0_params[2][0], d0_params[2][1], d0_params[2][2]);
	RooRealVar b("b", "b", d0_params[3][0], d0_params[3][1], d0_params[3][2]);
	RooGenericPdf f_bgr("f_bgr","background model", "lambda_b_mass * pow(((pow(lambda_b_mass, 2) / pow(m_thr, 2)) -1), c1) * exp(-lambda_b_mass * c2) * (1 - exp(-(lambda_b_mass - m_thr)/b))", RooArgSet(mass, m_thr, c1, c2, b));
	
	//Señal Breit-Wigner
	RooRealVar mean("mean","mean of breit-wigner", mean_range[0], mean_range[1], mean_range[2]);
	RooRealVar gamma("gamma", "mean of gaussian", gamma_range[0], gamma_range[1], gamma_range[2]) ;
	RooBreitWigner breit_wigner("breit_wigner", "Breit-Wigner Signal", mass, mean, gamma);
	
	//Dataset
	RooDataSet* data = new RooDataSet("data", "datos del 2012 filtrados", ntuple, mass);
	
	//Se combina señal (Breit-Wigner) y background DØ
	RooRealVar fracc_breit("fracc_breit","fraccion de señal", background_fraction[0], background_fraction[1], background_fraction[2]);
	RooAddPdf model_breit("model_gauss","modelo Breit-Wigner + DØ", breit_wigner, f_bgr, fracc_breit);
	
	//Dibuja los histogramas
	RooPlot* frame_breit = mass.frame(Title("Breit-Wigner"), Bins(bin_number));
	
	//Se dibujan los datos en el frame y se ajustan los modelos
	data->plotOn(frame_breit);
	RooFitResult* model_breit_result = model_breit.fitTo(*data, Save(kTRUE), NumCPU(4));
	model_breit.plotOn(frame_breit, LineColor(kBlue));
	
	//Crea el pull para cada ajuste
	RooHist* hpull_breit = frame_breit->pullHist();
	RooPlot* frame7 = mass.frame(Title("Pull Distribution (Breit-Wigner)"));
	frame7->addPlotable(hpull_breit,"PY");
	
	//Dibuja el background de cada modelo
	model_breit.plotOn(frame_breit,Components(f_bgr),LineStyle(kDashed));
	
	//Dibuja la señal de cada modelo
	model_breit.plotOn(frame_breit,Components(breit_wigner), LineStyle(kDotted), LineColor(kRed), NumCPU(4));
	
	//Print structure of composite p.d.f.
	model_breit.Print("t");
	
	//Ahora el procedimiento para calcular la signficancia del pico:
	Double_t minNLLAll = model_breit_result->minNll();
	mean.setConstant(kTRUE);
	gamma.setConstant(kTRUE);
	fracc_breit.setVal(1.0);
	fracc_breit.setConstant(kTRUE);
	RooFitResult* fitresbkg = model_breit.fitTo(*data, Save(kTRUE), NumCPU(4));
	Double_t minNLLBkg = fitresbkg->minNll();
	
	fitresbkg->Print("v");
	cout<<" -Log Likelihood values : "<<minNLLAll<<"  "<<minNLLBkg<<endl;
	cout<<" -Log likelihood ratio : "<<minNLLBkg - minNLLAll<<endl; // -ln(L_bkg) - -ln(L_sig+ L_bkg) = -ln[L_bkg/(L_sig+L_bkg) = -ln(R) = ln(1/R)
	cout<<" Likelihood ratio : "<<1/TMath::Exp(minNLLBkg - minNLLAll)<<endl;
	Double_t sigLR = sqrt(2.*(minNLLBkg - minNLLAll)); // sqrt[-2*ln(R)]
	
	cout<<" Significance from LR : "<<sigLR<<endl;  //Signficancia final del pico por medio de LR.
	
	std::string path = "Resultados/Histogramas/Fit/Finales/";
	
	//Dibuja los canvas para cada fit y su pull
	TCanvas* canvas_breit = new TCanvas("canvas_breit", "DØ + Breit-Wigner", 600, 600);
	std::string filename_breit = "DØ Breit-Wigner";
	TString path_breit = path + filename_breit + ".png";
	canvas_breit->cd();
	frame_breit->GetYaxis()->SetTitleOffset(1.6);
	gPad->SetTicks(1, 1);
	frame_breit->Draw();
	//	canvas_breit->Print(path_breit.Data());
	
	TCanvas* canvas_breit_pull = new TCanvas("canvas_breit_pull", "Pull Distribution (Breit-Wigner)", 600, 600);
	std::string filename_breit_pull = "DØ Breit-Wigner Pull";
	TString path_breit_pull = path + filename_breit_pull + ".png";
	canvas_breit_pull->cd();
	frame7->GetYaxis()->SetTitleOffset(1.6);
	gPad->SetTicks(1, 1);
	frame7->Draw();
	//	canvas_breit_pull->Print(path_breit_pull.Data());
}

void fit_breit_wigner_fija(std::string data_path, std::string ntuple_name, std::string variable_name, std::string variable_description, std::vector<float> variable_range, float mean_value, float gamma_value, std::vector<vector<float>> d0_params, std::vector<float> background_fraction, unsigned int bin_number){
	//Lee los datos filtrados del archivo
	TFile* file = new TFile(data_path.data(), "READ");
	TTree* ntuple = nullptr;
	file->GetObject(ntuple_name.data(), ntuple);
	
	//Observable
	RooRealVar mass(variable_name.data(), variable_description.data(), variable_range[0], variable_range[1]) ;
	
	//Background DØ
	RooRealVar m_thr("m_thr", "m_thr", d0_params[0][0]);
	RooRealVar c1("c1", "c1", d0_params[1][0], d0_params[1][1], d0_params[1][2]);
	RooRealVar c2("c2", "c2", d0_params[2][0], d0_params[2][1], d0_params[2][2]);
	RooRealVar b("b", "b", d0_params[3][0], d0_params[3][1], d0_params[3][2]);
	
	std::string formula = "lambda_b_mass * pow(((pow(lambda_b_mass, 2) / pow(m_thr, 2)) -1), c1) * exp(-lambda_b_mass * c2) * (1 - exp(-(lambda_b_mass - m_thr)/b))";
//	const char * variable_const = variable_name.c_str();
//	std::replace(formula.begin(), formula.end(), "variable", "lambda_b_mass");
	
	RooGenericPdf f_bgr("f_bgr", "background model", formula.data(), RooArgSet(mass, m_thr, c1, c2, b));
	
	//Señal Breit-Wigner
	RooRealVar mean("mean","mean of breit-wigner", mean_value);
	RooRealVar gamma("gamma", "mean of gaussian", gamma_value) ;
	RooBreitWigner breit_wigner("breit_wigner", "Breit-Wigner Signal", mass, mean, gamma);
	
	//Dataset
	RooDataSet* data = new RooDataSet("data", "datos del 2012 filtrados", ntuple, mass);
	
	//Se combina señal (Breit-Wigner) y background DØ
	RooRealVar fracc("fracc","fraccion de señal", background_fraction[0], background_fraction[1], background_fraction[2]);
	RooAddPdf model_breit_fixed("model_breit_fixed","modelo Breit-Wigner + DØ", breit_wigner, f_bgr, fracc);
	
	//Dibuja los histogramas
	RooPlot* frame_breit_fixed = mass.frame(Title("Breit-Wigner Fija"), Bins(bin_number));
	
	//Se dibujan los datos en el frame y se ajustan los modelos
	data->plotOn(frame_breit_fixed);
	RooFitResult* model_breit_fixed_result = model_breit_fixed.fitTo(*data, Save(kTRUE), NumCPU(4));
	model_breit_fixed.plotOn(frame_breit_fixed, LineColor(kBlue));
	
	//Crea el pull para cada ajuste
	RooHist* hpull_breit_fixed = frame_breit_fixed->pullHist();
	RooPlot* frame7 = mass.frame(Title("Pull Distribution Fija (Breit-Wigner)"));
	frame7->addPlotable(hpull_breit_fixed,"PY");
	
	//Dibuja el background de cada modelo
	model_breit_fixed.plotOn(frame_breit_fixed,Components(f_bgr),LineStyle(kDashed));
	
	//Dibuja la señal de cada modelo
	model_breit_fixed.plotOn(frame_breit_fixed,Components(breit_wigner), LineStyle(kDotted), LineColor(kRed), NumCPU(4));
	
	//Print structure of composite p.d.f.
	model_breit_fixed.Print("t");
	
	//Ahora el procedimiento para calcular la signficancia del pico:
	Double_t minNLLAll = model_breit_fixed_result->minNll();
	mean.setConstant(kTRUE);
	gamma.setConstant(kTRUE);
	fracc.setVal(1.0);
	fracc.setConstant(kTRUE);
	RooFitResult* fitresbkg = model_breit_fixed.fitTo(*data, Save(kTRUE), NumCPU(4));
	Double_t minNLLBkg = fitresbkg->minNll();
	
	fitresbkg->Print("v");
	cout<<" -Log Likelihood values : "<<minNLLAll<<"  "<<minNLLBkg<<endl;
	cout<<" -Log likelihood ratio : "<<minNLLBkg - minNLLAll<<endl; // -ln(L_bkg) - -ln(L_sig+ L_bkg) = -ln[L_bkg/(L_sig+L_bkg) = -ln(R) = ln(1/R)
	cout<<" Likelihood ratio : "<<1/TMath::Exp(minNLLBkg - minNLLAll)<<endl;
	Double_t sigLR = sqrt(2.*(minNLLBkg - minNLLAll)); // sqrt[-2*ln(R)]
	
	cout<<" Significance from LR : "<<sigLR<<endl;  //Signficancia final del pico por medio de LR.
	
	std::string path = "Resultados/Histogramas/Fit/Finales/";
	
	//Dibuja los canvas para cada fit y su pull
	TCanvas* canvas_breit_fixed = new TCanvas("canvas_breit_fixed", "DØ + Breit-Wigner (Fija)", 600, 600);
	std::string filename_breit_fixed = "DØ Breit-Wigner (Fija)";
	TString path_breit = path + filename_breit_fixed + ".png";
	canvas_breit_fixed->cd();
	frame_breit_fixed->GetYaxis()->SetTitleOffset(1.6);
	gPad->SetTicks(1, 1);
	frame_breit_fixed->Draw();
	//	canvas_breit_fixed->Print(path_breit_fixed.Data());
	
	TCanvas* canvas_breit_fixed_pull = new TCanvas("canvas_breit_fixed_pull", "Pull Distribution (Breit-Wigner Fija)", 600, 600);
	std::string filename_breit_fixed_pull = "DØ Breit-Wigner (Fija) Pull";
	TString path_breit_fixed_pull = path + filename_breit_fixed_pull + ".png";
	canvas_breit_fixed_pull->cd();
	frame7->GetYaxis()->SetTitleOffset(1.6);
	gPad->SetTicks(1, 1);
	frame7->Draw();
	//	canvas_breit_fixed_pull->Print(path_breit_fixed_pull.Data());
}

void fit_gauss_fija(std::string data_path, std::string ntuple_name, std::string variable_name, std::string variable_description, std::vector<float> variable_range, float mean_value, float sigma_value, std::vector<vector<float>> d0_params, std::vector<float> background_fraction, unsigned int bin_number){
	
	//Lee los datos filtrados del archivo
	TFile* file = new TFile(data_path.data(), "READ");
	TTree* ntuple = nullptr;
	file->GetObject(ntuple_name.data(), ntuple);
	
	//Observable
	RooRealVar mass(variable_name.data(), variable_description.data(), variable_range[0], variable_range[1]) ;
	
	//Background DØ
	RooRealVar m_thr("m_thr", "m_thr", d0_params[0][0]);
	RooRealVar c1("c1", "c1", d0_params[1][0], d0_params[1][1], d0_params[1][2]);
	RooRealVar c2("c2", "c2", d0_params[2][0], d0_params[2][1], d0_params[2][2]);
	RooRealVar b("b", "b", d0_params[3][0], d0_params[3][1], d0_params[3][2]);
	RooGenericPdf f_bgr("f_bgr","background model", "lambda_b_mass * pow(((pow(lambda_b_mass, 2) / pow(m_thr, 2)) -1), c1) * exp(-lambda_b_mass * c2) * (1 - exp(-(lambda_b_mass - m_thr)/b))", RooArgSet(mass, m_thr, c1, c2, b));
	
	//Señal Gaussiana Fija
	RooRealVar mean("mean", "mean of gaussian", mean_value);
	RooRealVar sigma("sigma", "width of gaussian", sigma_value);
	RooGaussian gaussian("gaussian", "Gaussian Signal", mass, mean, sigma);
	
	//Dataset
	RooDataSet* data = new RooDataSet("data", "datos del 2012 filtrados", ntuple, mass);
	
	//Se combina señal (Gaussiana Fija) y background DØ
	RooRealVar fraction("fraction","fraccion de señal", background_fraction[0], background_fraction[1], background_fraction[2]);
	RooAddPdf model_gauss("model_gauss","modelo Gauss + DØ Fijo", gaussian, f_bgr, fraction);
	
	//Dibuja los histogramas
	RooPlot* frame_histo = mass.frame(Title("Gaussiana (Fija)"), Bins(bin_number));
	
	//Se dibujan los datos en el frame y se ajustan los modelos
	data->plotOn(frame_histo);
	RooFitResult* result = model_gauss.fitTo(*data, Save(kTRUE), NumCPU(4));
	model_gauss.plotOn(frame_histo, LineColor(kBlue));
	
	//Crea el pull para cada ajuste
	RooHist* hpull = frame_histo->pullHist();
	RooPlot* frame_pull = mass.frame(Title("Pull Distribution (Gauss Fijo)"));
	frame_pull->addPlotable(hpull,"PY");
	
	//Dibuja el background de cada modelo
	model_gauss.plotOn(frame_histo,Components(f_bgr),LineStyle(kDashed));
	
	//Dibuja la señal de cada modelo
	model_gauss.plotOn(frame_histo,Components(gaussian), LineStyle(kDotted), LineColor(kRed), NumCPU(4));
	
	//Print structure of composite p.d.f.
	model_gauss.Print("v");
	
	//Ahora el procedimiento para calcular la signficancia del pico:
	Double_t minNLLAll = result->minNll();
	mean.setConstant(kTRUE);
	sigma.setConstant(kTRUE);
	fraction.setVal(1.0);
	fraction.setConstant(kTRUE);
	RooFitResult* fitresbkg = model_gauss.fitTo(*data, Save(kTRUE), NumCPU(4));
	Double_t minNLLBkg = fitresbkg->minNll();
	
	fitresbkg->Print("v");
	cout<<" -Log Likelihood values : "<<minNLLAll<<"  "<<minNLLBkg<<endl;
	cout<<" -Log likelihood ratio : "<<minNLLBkg - minNLLAll<<endl; // -ln(L_bkg) - -ln(L_sig+ L_bkg) = -ln[L_bkg/(L_sig+L_bkg) = -ln(R) = ln(1/R)
	cout<<" Likelihood ratio : "<<1/TMath::Exp(minNLLBkg - minNLLAll)<<endl;
	Double_t sigLR = sqrt(2.*(minNLLBkg - minNLLAll)); // sqrt[-2*ln(R)]
	
	cout<<" Significance from LR : "<<sigLR<<endl;  //Signficancia final del pico por medio de LR.
	
	std::string path = "Resultados/Histogramas/Fit/Finales/";
	
	//Dibuja los canvas para cada fit y su pull
	TCanvas* canvas_histo = new TCanvas("canvas_gauss_fixed", "DØ + Gaussian (Fija)", 600, 600);
	std::string filename_histo = "DØ Gaussian";
	TString path_histo = path + filename_histo + ".png";
	canvas_histo->cd();
	frame_histo->GetYaxis()->SetTitleOffset(1.6);
	gPad->SetTicks(1, 1);
	frame_histo->Draw();
	//	canvas_histo->Print(path_histo.Data());
	
	TCanvas* canvas_pull = new TCanvas("canvas_gauss_fixed_pull", "Pull Distribution (Gaussian)", 600, 600);
	std::string filename_pull = "DØ Gaussian Pull";
	TString path_pull = path + filename_pull + ".png";
	canvas_pull->cd();
	frame_pull->GetYaxis()->SetTitleOffset(1.6);
	gPad->SetTicks(1, 1);
	frame_pull->Draw();
	//	canvas_pull->Print(path_pull.Data());
}

void fit_gauss(std::string data_path, std::string ntuple_name, std::string variable_name, std::string variable_description, std::vector<float> variable_range, std::vector<float> mean_range, std::vector<float> sigma_range, std::vector<vector<float>> d0_params, std::vector<float> background_fraction, unsigned int bin_number){
	
	//Lee los datos filtrados del archivo
	TFile* file = new TFile(data_path.data(), "READ");
	TTree* ntuple = nullptr;
	file->GetObject(ntuple_name.data(), ntuple);
	
	//Observable
	RooRealVar mass(variable_name.data(), variable_description.data(), variable_range[0], variable_range[1]) ;
	
	//Background DØ
	RooRealVar m_thr("m_thr", "m_thr", d0_params[0][0]);
	RooRealVar c1("c1", "c1", d0_params[1][0], d0_params[1][1], d0_params[1][2]);
	RooRealVar c2("c2", "c2", d0_params[2][0], d0_params[2][1], d0_params[2][2]);
	RooRealVar b("b", "b", d0_params[3][0], d0_params[3][1], d0_params[3][2]);
	RooGenericPdf f_bgr("f_bgr","background model", "lambda_b_mass * pow(((pow(lambda_b_mass, 2) / pow(m_thr, 2)) -1), c1) * exp(-lambda_b_mass * c2) * (1 - exp(-(lambda_b_mass - m_thr)/b))", RooArgSet(mass, m_thr, c1, c2, b));
	
	//Señal Gaussiana Fija
	RooRealVar mean_gauss_fixed("mean_gauss_fixed", "mean of gaussian", mean_range[0], mean_range[1], mean_range[2]);
	RooRealVar sigma_fixed("sigma_fixed", "width of gaussian", sigma_range[0], sigma_range[1], sigma_range[2]);
	RooGaussian sig_gauss_fixed("sig_gauss_fixed", "Gaussian Signal", mass, mean_gauss_fixed, sigma_fixed);
	
	//Dataset
	RooDataSet* data = new RooDataSet("data", "datos del 2012 filtrados", ntuple, mass);
	
	//Se combina señal (Gaussiana Fija) y background DØ
	RooRealVar fracc_gauss_fixed("frac_gauss_fixed","fraccion de señal",background_fraction[0], background_fraction[1], background_fraction[2]);
	RooAddPdf model_gauss_fixed("model_gauss_fixed","modelo Gauss + DØ Fijo", sig_gauss_fixed, f_bgr, fracc_gauss_fixed);
	
	//Dibuja los histogramas
	RooPlot* frame_gauss_fixed = mass.frame(Title("Gaussian (Fijo)"),Bins(bin_number));
	
	//Se dibujan los datos en el frame y se ajustan los modelos
	data->plotOn(frame_gauss_fixed);
	RooFitResult* model_gauss_result = model_gauss_fixed.fitTo(*data, Save(kTRUE), NumCPU(4));
	model_gauss_fixed.plotOn(frame_gauss_fixed, LineColor(kBlue));
	
	//Crea el pull para cada ajuste
	RooHist* hpull_gauss_fixed = frame_gauss_fixed->pullHist();
	RooPlot* frame6 = mass.frame(Title("Pull Distribution (Gauss Fijo)"));
	frame6->addPlotable(hpull_gauss_fixed,"PY");
	
	//Dibuja el background de cada modelo
	model_gauss_fixed.plotOn(frame_gauss_fixed,Components(f_bgr),LineStyle(kDashed));
	
	//Dibuja la señal de cada modelo
	model_gauss_fixed.plotOn(frame_gauss_fixed,Components(sig_gauss_fixed), LineStyle(kDotted), LineColor(kRed), NumCPU(4));
	
	//Print structure of composite p.d.f.
	model_gauss_fixed.Print("v");
	
	//Ahora el procedimiento para calcular la signficancia del pico:
	Double_t minNLLAll = model_gauss_result->minNll();
	mean_gauss_fixed.setConstant(kTRUE);
	sigma_fixed.setConstant(kTRUE);
	fracc_gauss_fixed.setVal(1.0);
	fracc_gauss_fixed.setConstant(kTRUE);
	RooFitResult* fitresbkg = model_gauss_fixed.fitTo(*data, Save(kTRUE), NumCPU(4));
	Double_t minNLLBkg = fitresbkg->minNll();
	
	fitresbkg->Print("v");
	cout<<" -Log Likelihood values : "<<minNLLAll<<"  "<<minNLLBkg<<endl;
	cout<<" -Log likelihood ratio : "<<minNLLBkg - minNLLAll<<endl; // -ln(L_bkg) - -ln(L_sig+ L_bkg) = -ln[L_bkg/(L_sig+L_bkg) = -ln(R) = ln(1/R)
	cout<<" Likelihood ratio : "<<1/TMath::Exp(minNLLBkg - minNLLAll)<<endl;
	Double_t sigLR = sqrt(2.*(minNLLBkg - minNLLAll)); // sqrt[-2*ln(R)]
	
	cout<<" Significance from LR : "<<sigLR<<endl;  //Signficancia final del pico por medio de LR.
	
	std::string path = "Resultados/Histogramas/Fit/Finales/";
	
	//Dibuja los canvas para cada fit y su pull
	TCanvas* canvas_gauss_fixed = new TCanvas("canvas_gauss_fixed", "DØ + Gaussian (Fija)", 600, 600);
	std::string filename_gauss_fixed = "DØ Gaussian (Fija)";
	TString path_gauss_fixed = path + filename_gauss_fixed + ".png";
	canvas_gauss_fixed->cd();
	frame_gauss_fixed->GetYaxis()->SetTitleOffset(1.6);
	gPad->SetTicks(1, 1);
	frame_gauss_fixed->Draw();
	//	canvas_gauss_fixed->Print(path_gauss_fixed.Data());
	
	TCanvas* canvas_gauss_fixed_pull = new TCanvas("canvas_gauss_fixed_pull", "Pull Distribution (Gaussian Fija)", 600, 600);
	std::string filename_gauss_fixed_pull = "DØ Gaussian (Fija) Pull";
	TString path_gauss_fixed_pull = path + filename_gauss_fixed_pull + ".png";
	canvas_gauss_fixed_pull->cd();
	frame6->GetYaxis()->SetTitleOffset(1.6);
	gPad->SetTicks(1, 1);
	frame6->Draw();
	//	canvas_gauss_fixed_pull->Print(path_gauss_fixed_pull.Data());
	
	
	
	
}

void fit_polinomio_d0(std::string data_path, std::string ntuple_name, std::string variable_name, std::string variable_description, std::vector<float> variable_range, std::vector<float> d0_params, unsigned int bin_number){
	//Lee los datos filtrados del archivo
	TFile* file = new TFile(data_path.data(), "READ");
	TTree* ntuple = nullptr;
	file->GetObject(ntuple_name.data(), ntuple);
	
	//Variable independiente
	RooRealVar mass(variable_name.data(), variable_description.data(), variable_range[0], variable_range[1]) ;
	
	//Background DØ
	RooRealVar m_thr("m_thr", "m_thr", d0_params[0]);
	RooRealVar c1("c1", "c1", d0_params[1]);
	RooRealVar c2("c2", "c2", d0_params[2]);
	RooRealVar b("b", "b", d0_params[3]);
	RooGenericPdf f_bgr("f_bgr","background model", "lambda_b_mass * pow(((pow(lambda_b_mass, 2) / pow(m_thr, 2)) -1), c1) * exp(-lambda_b_mass * c2) * (1 - exp(-(lambda_b_mass - m_thr)/b))", RooArgSet(mass, m_thr, c1, c2, b));
	
	//Dataset
	RooDataSet* data = new RooDataSet("data", "datos del 2012 filtrados", ntuple, mass);
	
	//Dibuja el histograma
	RooPlot* frame_data = mass.frame(Title(variable_description.data()), Bins(bin_number));
	
	//Se dibujan los datos en el frame y se ajusta el modelo
	data->plotOn(frame_data);
	f_bgr.fitTo(*data, NumCPU(4));
	f_bgr.plotOn(frame_data, LineColor(kBlue));
	
	//	 Overlay the background component of model with a dashed line
	RooHist* hpull = frame_data->pullHist() ;
	RooPlot* frame_hpull = mass.frame(Title("Background DØ Pull Distribution")) ;
	frame_hpull->addPlotable(hpull, "PZ");
	
	//	 Print structure of composite p.d.f.
	f_bgr.Print("t") ;
	
	TCanvas* canvas_data = new TCanvas("fit_pico", "Background DØ", 600, 600);
	TCanvas* canvas_hpull = new TCanvas("fit_pico2", "Background DØ Pull Distribution", 600, 600);
	canvas_data->cd();
	frame_data->GetYaxis()->SetTitleOffset(1.6);
	frame_data->Draw();
	
	canvas_hpull->cd();
	frame_hpull->GetYaxis()->SetTitleOffset(1.6);
	gPad->SetTicks(1, 1);
	frame_hpull->Draw();
}
