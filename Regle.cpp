/////////////////////////////////////////////////////////////////////////////
//Fichier Regle.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file Regle.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Regle
 * \author Charles Dion-Buteau
 * \version 0.1
 * \date fév. 2024
 *
 */

#include "Regle.h"

namespace tp1
{


    /**
      * \fn             Regle()
      * \brief          Constructeur de la classe règle
      * \param[in]
      * \pre
      * \post
      * \exception
     */
    Regle::Regle() : premisses(), conclusions(){
        //On ajoute ici des listes de prémisses et de conclusions vide afin de pouvoir les remplir par la suite
    };

    /**
      * \fn             Regle(const Regle & r)
      * \brief          Constructeur par copie de la classe règle
      * \param[in]      r Regle à copier
      * \pre
      * \post
      * \exception
     */
    Regle::Regle(const Regle & r): premisses(r.premisses), conclusions(r.conclusions){};

    /**
      * \fn             ~Regle(const Regle & r)
      * \brief          Destructeur de la classe règle
      * \param[in]
      * \pre
      * \post
      * \exception
     */
    Regle::~Regle() = default;


    /**
      * \fn             operator = (const Regle & r)
      * \brief          surcharge de l’opérateur =
      * \param[in]
      * \pre
      * \post
      * \exception
     */
    Regle & Regle::operator = (const Regle & r)
    {
        //Si l'objet à droite r n'est pas l'objet courant on y copie les premisses et conclusions de r
        if (this != &r)
        {
            premisses = r.premisses;
            conclusions = r.conclusions;
        }
        return *this;
    }


    /**
     * \fn             operator == (const Regle& r) const
     * \brief          surcharge de l’opérateur ==
     * \param[in]
     * \pre
     * \post
     * \exception
    */
    bool Regle::operator == (const Regle& r) const
    {
        return (premisses == r.premisses) && (conclusions == r.conclusions);
    }


    /**
     * \fn             operator != (const Regle& r) const
     * \brief          surcharge de l’opérateur !=
     * \param[in]
     * \pre
     * \post
     * \exception
    */
    bool Regle::operator != (const Regle& r) const
    {
        return (premisses != r.premisses) || (conclusions != r.conclusions);
    }

}
