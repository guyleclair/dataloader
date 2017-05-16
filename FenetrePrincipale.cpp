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
	
	// connection pour nouveau fichier
    connect( actionOuvrir,SIGNAL(triggered()),this,SLOT(ouvrirFichier()) );


	// connections pour les actions d'infos
	connect( actionAbout,SIGNAL(triggered()),this,SLOT(afficher_infos()) );
	connect( actionAboutQt,SIGNAL(triggered()),this,SLOT(afficher_infos_qt()) );
	
	chargementDonnees=new QProgressBar;
	statusBar()->addPermanentWidget(chargementDonnees);
	
	
	zoneCentrale = new QLabel(this);
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
				
		QImage image(&donnees[0],3712,3712,QImage::Format_Indexed8);
		image.setColorTable(table);

		//zoneCentrale->setBackgroundRole(QPalette::Base);
		zoneCentrale->setPixmap(QPixmap::fromImage(image));
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


/** Private slots */
void FenetrePrincipale::ouvrirFichier()
{
	std::string REP_HOME= getenv("HOME");
	if (getenv("HOME") != nullptr)
	{
		const QString rep_fichiers=getenv("HOME");
	}
	else throw std::bad_alloc();
	// Creation du fichier avec le nom choisi dans fenetre_save
	QString nom_fichier = QFileDialog::getOpenFileName(this, tr("Ouvrir"),"/home/milletj/Documents/Radar","hdf5 (*.hdf *.hdf5 *.h5)");
	if (nom_fichier == nullptr)
		return;
	const H5std_string nom_fichier_hdf5(nom_fichier.toStdString());
	afficher_fichier(nom_fichier_hdf5);
}


/** Public slots */
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
