#include "FenetrePrincipale.h"


FenetrePrincipale::FenetrePrincipale()
{
	/** Creation des menus, barre d'outils */
	creerMenus();
	creerBarresOutils();
    creerActions();

	/** Connections */
	connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
	
	// connection pour nouvel onglet
    connect( actionOuvrir,SIGNAL(triggered()),this,SLOT(ouvrirFichier()) );


	// connections pour les actions d'infos
	connect( actionAbout,SIGNAL(triggered()),this,SLOT(afficher_infos()) );
	connect( actionAboutQt,SIGNAL(triggered()),this,SLOT(afficher_infos_qt()) );
	chargementPage=new QProgressBar;
	statusBar()->addPermanentWidget(chargementPage);
	
	
	QWidget *zoneCentrale = new QWidget(this);
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

	//	
	actionExporter=menuFichier->addAction(tr("&Exporter au format JSON"));
	
	// Quitter
	actionQuitter=menuFichier->addAction("&Quitter");
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
	
}


/** PRIVATE SLOTS */


void FenetrePrincipale::ouvrirFichier()
{
	// Cretion du fichier avec le nom choisi dans fenetre_save
	QString nom_fichier = QFileDialog::getSaveFileName(this, tr("Save File"),"/home/milletj",tr("Header (*.h)"));
	
	
}


FenetrePrincipale::~FenetrePrincipale()
{
    
}

