#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include  <QProgressBar>
#include <QMenuBar>
#include <QStyle>
#include <QApplication>
#include <QToolBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QLabel>

#include <iostream>
#include "h5utils.h"



/**
 * @brief The FenetrePrincipale class
 */
class FenetrePrincipale : public QMainWindow
{
	Q_OBJECT

	private:
		
		QLabel* zoneCentrale;
		QGraphicsScene* sceneImage;
		QGraphicsView * viewImage;	// fenetre d'affichage des fichiers
		
		QMenu* menuFichier;
        QMenu* menuInfos;
        QToolBar* toolBar;
				
		QAction* actionComparer;
		QAction* actionOuvrir;
		QAction* actionFermer;
		QAction* actionQuitter;
		QAction* actionAnnuler;
		QAction* actionAbout;
		QAction* actionAboutQt;
		QAction* actionExporter;

		QProgressBar* chargementDonnees;

	public:
		FenetrePrincipale();
		void creerMenus();
		void creerActions();
		void creerBarresOutils();
		void afficher_fichier(const H5std_string & nom_fichier);
		~FenetrePrincipale();
		
	public slots:
		void ouvrirFichier();
		void afficher_infos();
		void afficher_infos_qt();
		
};

#endif // FENETREPRINCIPALE_H
