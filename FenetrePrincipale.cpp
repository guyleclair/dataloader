#include "FenetrePrincipale.h"


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

	//	export au format JSON
	actionExporter=menuFichier->addAction(tr("&Exporter au format JSON"));
	
	// Quitter
	actionQuitter=menuFichier->addAction("&Quitter");
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
	
	/* Actions du menu infos (?) */
	actionAbout=menuInfos->addAction(tr("A propos..."));
    actionAboutQt=menuInfos->addAction(tr("A propos de Qt..."));

}


/** Private slots */

void FenetrePrincipale::ouvrirFichier()
{
    std::string REP_HOME= getenv("HOME");
	if (getenv("HOME") != NULL)
	{
		const QString rep_fichiers=getenv("HOME");
	}
	else throw std::bad_alloc();
	// Creation du fichier avec le nom choisi dans fenetre_save
    QString nom_fichier = QFileDialog::getOpenFileName(this, tr("Ouvrir"),"/home/milletj",tr("hdf (*.hdf,*.hdf5)"));
	
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

