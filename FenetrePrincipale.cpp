#include "FenetrePrincipale.h"


/**
 * @brief FenetrePrincipale::FenetrePrincipale Constructeur par defaut
 */
FenetrePrincipale::FenetrePrincipale()
{
	/** Creation des menus, barre d'outils */
	creerMenus();
	creerBarresOutils();
	creerActions();

	/** Connections */
	connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
	// connections pour menus ouvrir, exporter
	connect( actionOuvrir,SIGNAL(triggered()),this,SLOT(ouvrirFichier()) );
	connect( actionExporter,SIGNAL(triggered()),this,SLOT(exporterHdf5Json()) );

	// connections pour les actions d'infos
	connect( actionAbout,SIGNAL(triggered()),this,SLOT(afficher_infos()) );
	connect( actionAboutQt,SIGNAL(triggered()),this,SLOT(afficher_infos_qt()) );

	chargementDonnees=new QProgressBar;
	statusBar()->addPermanentWidget(chargementDonnees);

	// Affichage du widget central
	zoneCentrale=new QWidget(this);
    setCentralWidget(zoneCentrale);

}


void FenetrePrincipale::creerMenus()
{
	menuFichier = menuBar()->addMenu("&Fichier");
    menuInfos = menuBar()->addMenu("&?");
}


void FenetrePrincipale::creerBarresOutils()
{
    toolBar=addToolBar("Comparaison");
}


void FenetrePrincipale::creerActions()
{
	//  On récupère un pointeur sur l'objet QStyle correspondant à l'application
	QStyle* style =  QApplication::style();
	
    /* Actions du menu Fichier */
	
	// Ouvrir un fichier
    actionOuvrir=menuFichier->addAction("&Ouvrir");
	// ajout dans la barre d'outils
	QIcon iconeOuvrir = style->standardIcon(QStyle::SP_DirOpenIcon);
	actionOuvrir->setShortcut(QKeySequence("Ctrl+O"));
	actionOuvrir->setIcon(iconeOuvrir);
    toolBar->addAction(actionOuvrir);

	//	export au format JSON
	actionExporter=menuFichier->addAction(tr("&Exporter au format JSON"));
	
	// Quitter
	actionQuitter=menuFichier->addAction("&Quitter");
	actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
	
	/* Actions du menu infos (?) */
	actionAbout=menuInfos->addAction(tr("A propos..."));
    actionAboutQt=menuInfos->addAction(tr("A propos de Qt..."));

}


/**
 * @brief FenetrePrincipale::afficher_fichier affiche un fichier hdf5
 * dans la fenetre
 * @param nom_fichier
 */
void FenetrePrincipale::afficher_fichier(const H5std_string & nom_fichier)
{
	try
	{

		// Ouverture du fichier
		H5::H5File fichier(nom_fichier, H5F_ACC_RDONLY );
		std::vector<unsigned char> donnees=get_donnees_CM(fichier);
		std::cout<< "Fin de recuperation  donnnees"<< std::endl;
		std::vector<std::vector<int>>  palette_CM = get_palette_CM(fichier);

		QVector<QRgb> table;
		for (unsigned short int i=0;i<palette_CM.size();i++)
		{
			std::cout<< palette_CM[i][0]<< ' '<< palette_CM[i][1]<< ' '<<palette_CM[i][2] << std::endl;
			table.push_back(qRgb(palette_CM[i][0],palette_CM[i][1],palette_CM[i][2]));
		}

		std::pair<int,int> dims=get_nx_ny(fichier);
		QImage image(&donnees[0],dims.first,dims.second,QImage::Format_Indexed8);
		image.setColorTable(table);

		//zoneCentrale->setBackgroundRole(QPalette::Base);
		
		QLabel* imageCentrale = new QLabel(this);
		imageCentrale->setPixmap(QPixmap::fromImage(image.scaled(QSize(512,512))));
		QTextEdit* infosFichier=new QTextEdit(tr("Metadonnées de l'image:"),this);
	
		
		QVBoxLayout *layout = new QVBoxLayout;
	    layout->addWidget(imageCentrale);
		layout->addWidget(infosFichier);
		zoneCentrale->setLayout(layout);
		zoneCentrale->show();
		
	}

	// catch failure caused by the H5File operations
	catch( H5::FileIException error )
	{
		error.printError();
		return;
	}
	// catch failure caused by the DataSet operations
	catch( H5::DataSetIException error )
	{
		error.printError();
		return;
	}
	// catch failure caused by the DataSpace operations
	catch( H5::DataSpaceIException error )
	{
		error.printError();
		return;
	}
	// catch failure caused by the DataSpace operations
	catch( H5::DataTypeIException error )
	{
		error.printError();
		return;
	}
	
}


/** Public slots */
void FenetrePrincipale::ouvrirFichier()
{
	std::string REP_HOME= getenv("HOME");
	QString rep_fichiers;
	if (getenv("HOME") != nullptr)
	{
		rep_fichiers=getenv("HOME");
	}
	else throw std::bad_alloc();
	// Creation du fichier avec le nom choisi dans fenetre_save
	QString nom_fichier = QFileDialog::getOpenFileName(this, tr("Ouvrir"),rep_fichiers,"hdf5 (*.hdf *.hdf5 *.h5)");
	if (nom_fichier == nullptr)
		return;
	const H5std_string nom_fichier_hdf5(nom_fichier.toStdString());
	afficher_fichier(nom_fichier_hdf5);
}


void FenetrePrincipale::exporterHdf5Json()
{
	std::string REP_HOME= getenv("HOME");
	QString rep_fichiers;
	if (getenv("HOME") != nullptr)
	{
		rep_fichiers=getenv("HOME");
	}
	else throw std::bad_alloc();
	// Creation du fichier avec le nom choisi dans fenetre_save
	QString nom_fichier = QFileDialog::getOpenFileName(this, tr("Ouvrir"),rep_fichiers,"hdf5 (*.hdf *.hdf5 *.h5)");
	if (nom_fichier == nullptr)
		return;
	const H5std_string nom_fichier_hdf5(nom_fichier.toStdString());
	hdf2Json(nom_fichier_hdf5);
}


void FenetrePrincipale::hdf2Json(const H5std_string & nom_fichier_hdf5)
{
	// Ouverture du fichier
	H5::H5File fichier(nom_fichier_hdf5, H5F_ACC_RDONLY );
	std::vector<Point3D> matrice_lue= get_donnees_3D(fichier);
	// pour tests
	matrice_lue.resize(10000); 
	// export des donnees en Json
	QJsonObject json;
	QJsonArray coordonees;
	QJsonArray valeurs;
	std::vector<Point3D>::iterator it;
	for(it=matrice_lue.begin();it!= matrice_lue.end();++it)
	{
		coordonees.push_back(it->px);
		coordonees.push_back(it->py);
		coordonees.push_back(it->pz);
		valeurs.push_back(it->value);
		valeurs.push_back(it->value);
		valeurs.push_back(it->value);
	}
	std::cout<<"taille de coordonees: "<< coordonees.size()<< std::endl;
	std::cout<<"taille de valeurs: "<< valeurs.size()<< std::endl;
	
	json["coordonees"]=coordonees;
	json["valeurs"]=valeurs;
	
	// Sauvegarde dans un fichier
	QFile saveFile(QStringLiteral("save_indented.json"));

	if (!saveFile.open(QIODevice::WriteOnly))
	{
		qWarning("Couldn't open save file.");
		return;
	}
	
	QJsonDocument docJson(json);
	saveFile.write(docJson.toJson(QJsonDocument::Indented));
	
}


void  FenetrePrincipale::afficher_infos()
{
    QMessageBox::about(this,"A propos de ce logiciel", "<b> dataloader </b> \n Version 1.0 \n");
}


void  FenetrePrincipale::afficher_infos_qt()
{
    QMessageBox::aboutQt(this);
}


FenetrePrincipale::~FenetrePrincipale()
{
    
}
