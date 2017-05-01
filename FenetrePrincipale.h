#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include  <QProgressBar>
#include <QMenuBar>
#include <QStyle>
#include <QApplication>
#include <QToolBar>


/**
 * @brief The FenetrePrincipale class
 */
class FenetrePrincipale : public QMainWindow
{
	Q_OBJECT

	private:
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
		~FenetrePrincipale();
		
	private slots:
		void ouvrirFichier();
		
};

#endif // FENETREPRINCIPALE_H
