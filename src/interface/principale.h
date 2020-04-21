#ifndef _principale_h
#define _principale_h

/** 
*	Affiche la page d'ouverture de l'application
*
*	@return void
**/
void page_ouverture();

/** 
*	Affiche la page de connexion
*
*	@return void
**/
void page_connexion();


/** 
*	Affiche la page d'inscription
*
*	@return void
**/
void page_inscription();


/** 
*	Affiche les notifications de l'interface correspondantes
*	au code passé en paramètre
*
*	@param	code int correspondant au code de la notification à afficher
*	@return	void
**/
void notification(int code);

#endif // !_principale_h