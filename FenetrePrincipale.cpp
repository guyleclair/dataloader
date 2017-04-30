#include "FenetrePrincipale.h"


FenetrePrincipale::FenetrePrincipale()
{
	creerMenus();
	creerBarresOutils();
    creerActions();
	

	QWidget *zoneCentrale = new QWidget;
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
	//const QString CHEMIN_PNG="/home/milletj/Projets/qt/intercomparaison";
	//  On récupère un pointeur sur l'objet QStyle correspondant à l'application
	QStyle* style =  QApplication::style();
	
    /* Actions du menu Fichier */
	
	// Ouvrir un fichier
    actionOuvrir=menuFichier->addAction("&Ouvrir");
	// ajout dans la barre d'outils
	QIcon iconeOuvrir = style->standardIcon(QStyle::SP_DirOpenIcon);
	actionOuvrir->setIcon(iconeOuvrir);
    toolBar->addAction(actionOuvrir);
	
	
	
    actionFermer=menuFichier->addAction("&Fermer");
    actionQuitter=menuFichier->addAction("&Quitter");
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
}


FenetrePrincipale::~FenetrePrincipale()
{
    
}
