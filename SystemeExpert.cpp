/**
 * \file SystemeExpert.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe SystemeExpert
 * \author Charles Dion-Buteau
 * \version 0.1
 * \date fév. 2024
 *
 */

#include "SystemeExpert.h"

namespace tp1 {
    // Compléter les méthodes demandées et corriger éventuellement la valeur de retour !
    // Ajouter aussi les balises Doxygen et commenter bien vos méthodes.

    //constructeur
    /**
     * \fn             SystemeExpert()
     * \brief          Constructeur de la classe SystemeExpert
     * \param[in]
     * \pre
     * \post
     * \exception
    */
    SystemeExpert::SystemeExpert() : baseRegles(), baseFaits() {
    }


    /**
     * \fn             ~SystemeExpert()
     * \brief          Destructeur de la classe SystemeExpert
     * \param[in]
     * \pre
     * \post
     * \exception
    */
    SystemeExpert::~SystemeExpert() = default;


    /**
     * \fn             SystemeExpert(const SystemeExpert &se)
     * \brief          constructeur de copie de la classe SystemeExpert
     * \param[in]
     * \pre
     * \post
     * \exception
    */
    SystemeExpert::SystemeExpert(const SystemeExpert &se) : baseRegles(se.baseRegles) {
    }


    /**
     * \fn             operator = (const SystemeExpert & se)
     * \brief          surcharge de l’opérateur =
     * \param[in]      SystemeExpert & se
     * \pre
     * \post
     * \exception
    */
    SystemeExpert &SystemeExpert::operator=(const SystemeExpert &se) {
        if (this != &se) {
            baseRegles = se.baseRegles;
            baseFaits = se.baseFaits;
        }

        return *this;
    }


    /**
     * \fn             ajouterRegleSE(const Regle & tr)
     * \brief          Permet d'ajouter la règle tr (déjà créée et initialisée) au système expert. Ne rien faire si elle existe déjà
     * \param[in]      SystemeExpert & tr
     * \pre
     * \post
     * \exception
    */
    void SystemeExpert::ajouterRegleSE(const Regle &tr) {
        //On créer un iterateur qui pointera sur la regle si elle existe deja
        auto itBase = std::find(baseRegles.begin(), baseRegles.end(), tr);
        //Si elle n'existe pas, l'iterateur va pointer sur le dernier élément du vecteur donc on ajoute la
        //regle à la base de regle
        if (itBase == baseRegles.end()) {
            baseRegles.push_back(tr);
        } else {
            //On lance une erreur de logique si la règle y est déjà
            throw std::logic_error("La règle existe déjà dans la base de règle");
        }
    }


    /**
    * \fn             ajouterFaitSE(const TypeFait & tf)
    * \brief          Permet d'ajouter la règle tr (déjà créée et initialisée) au système expert. Ne rien faire si elle existe déjà
    * \param[in]      SystemeExpert & tr
    * \pre
    * \post
    * \exception      std::logic_error si le fait entré est vide
   */
    void SystemeExpert::ajouterFaitSE(const TypeFait &tf) {
        if(tf.empty()) throw std::logic_error("Le fait entre est vide.");
        //On crée un iterateur qui pointera sur le fait s'il existe déjà
        auto itFait = std::find(baseFaits.begin(), baseFaits.end(), tf);
        //Si il n'existe pas, l'iterateur va pointer sur le dernier élément du vecteur donc on ajoute le
        //fait à la base de faits
        if (itFait == baseFaits.end()) {
            baseFaits.push_back(tf);
        } else {
            //On lance une erreur de logique si la règle y est déjà
            throw std::logic_error("Le fait existe deja dans la base de faits");
        }
    }


    /**
    * \fn             ajouterFaitSE(const TypeFait & tf)
    * \brief          Permet de charger un système expert à partir d'un fichier texte reçu en paramètre.
    *                 Le fichier EntreeFichier a déjà été ouvert à l'aide de la méthode "open", préalablement à l'appel de la fonction "chargerSE"
    * \param[in]      std::ifstream &EntreeFichier
    * \pre
    * \post
    * \exception      std::logic_error si le fichier n'est pas ouvert
   */
    void SystemeExpert::chargerSE(std::ifstream &EntreeFichier) {
        Regle regle;        // Règle qui sera ajoutée au Système Expert.
        TypeFait faitLu;    // fait qui sera ajoutée soit à 'regle' soit à la base de faits.
        int section = 1;    // section 1: Premisses d'une règle.
        // section 2: Conclusions d'une règle.
        // section 3: Faits de base.

        // Vérifier si le fichier est ouvert en lecture
        if (!EntreeFichier.is_open()) throw std::logic_error("chargerSE: le fichier n'est pas ouvert");


        while (!EntreeFichier.eof()) // Jusqu'à ce qu'on ai atteint la fin du fichier
        {
            getline(EntreeFichier, faitLu);
            if (faitLu[0] == '!')    // Dans le format du fichier, le caractère '!'
            {                        // indique un changement de section
                if (faitLu[1] == '>')    // "!>" indique que la prochaine section
                    section = 2;        // contient des conclusions.
                else {
                    // La dernière section contenait des conclusions donc on
                    // vient de finaliser une règle.  On l'ajoute maintenant au Système Expert
                    ajouterRegleSE(regle);
                    //Vider la règle en supprimant ses prémisses et ses conclusions
                    regle.GetPremisses().clear();
                    regle.GetConclusions().clear();

                    section = (faitLu[1] == '%') ? 1 : 3;
                    // "!%" indique que la prochaine section contient
                    //	des premisses.
                    // "!!" indique que la prochaine section contient
                    //	des faits.
                }

                getline(EntreeFichier, faitLu);
            }

            switch (section) {
                case 1:  // Ajout d'une premisse à une règle
                    regle.GetPremisses().push_back(faitLu);
                    break;

                case 2:    // Ajout d'une conclusion à une règle
                    regle.GetConclusions().push_back(faitLu);
                    break;

                case 3:    // Ajout d'un fait à la base de faits
                    ajouterFaitSE(faitLu);
                    break;
            }
        }
    }


    /**
    * \fn            chainageAvant(std::vector<Regle> & er)
    * \brief         Permet de saturer la base de faits du système expert se en retrouvant
		             les faits qui peuvent être déduits de la base de faits du système expert en question
		             et en se basant sur les règles de celui-ci. Cette fonction retourne donc l’ensemble de règles qui ont
		             permis à déduire de nouveaux faits.
    * \param[in]     std::vector<Regle> & er
    * \pre
    * \post
    * \exception     std::logic_error  si la base de fait est vide
    * \exception     std::logic_error  si la base de regle est vide
   */
    void SystemeExpert::chainageAvant(std::vector<Regle> &er) {

        //On vérifie d'abord si la base de regles ou de faits est vide
        //Si c'est le cas, on lance un erreur de logic car impossible defaire le chainage avant
        if (baseRegles.empty()) {
            throw std::logic_error(
                    "Base de règle vide donc impossible de d'effectuer une chainage avant. Veuillez recommencer avec une base de règles valide.");
        }
        if (baseFaits.empty()) {
            throw std::logic_error(
                    "Base de faits vide donc impossible de d'effectuer une chainage avant. Veuillez recommencer avec une base de faits valide.");
        }

        //On clear le vecteur de regle qui a deduit des nouveaux faits pour pouvoir le re-remplir
        er.clear();
        //Création d'un flag qui me dit si un nouveau fait a été déduit
        int flagNouvFait = 1;

        while (flagNouvFait) {
            //on met le flag des premisses a 0 à chaque nouvelle iteration, il servira à vérifier si on trouve une nouvelle conclusion
            flagNouvFait = 0;

            for (auto itBaseR = baseRegles.begin(); itBaseR != baseRegles.end(); ++itBaseR) {

                int flagPrem = 1;
                //Tant que flagprem == 1, on boucle sur les premisse de chaque regle
                for (auto itPre = itBaseR->GetPremisses().begin();
                     itPre != itBaseR->GetPremisses().end() && flagPrem == 1; ++itPre) {
                    auto nouvPremisse = find(baseFaits.begin(), baseFaits.end(), *itPre);

                    if (nouvPremisse == baseFaits.end()) {
                        //Si jamais on ne trouve pas la premisse dans la base de fait on met
                        //le flag des premisse à 0 -> pas de nouvelle conclusion
                        flagPrem = 0;
                    }
                }
                if (flagPrem == 1) {
                    //Nouvelle conclusions!
                    for (auto itConcl = itBaseR->GetConclusions().begin();
                         itConcl != itBaseR->GetConclusions().end(); ++itConcl) {
                        auto conclDejaPres = find(baseFaits.begin(), baseFaits.end(), *itConcl);
                        if (conclDejaPres == baseFaits.end()) {
                            //La conclusion ne fait pas partie de la base de faits -> on l'ajoute!
                            baseFaits.push_back(*itConcl);
                            er.push_back(*itBaseR);
                            flagNouvFait = 1;
                        }

                    }

                }
            }
        }


    }


    /**
    * \fn            std::vector<Regle> SystemeExpert::chainageArriere (const TypeFait & hypothese, bool & demontre)
    * \brief         fonction récursive qui permet de démontrer
                     la véracité du fait hypothese en se basant sur les faits et les règles du système expert.
                     Si celui-ci est démontré, la valeur VRAI est retournée dans demontre, FAUX sinon.
    * \param[in]     const TypeFait & hypothese
    * \param[in]     bool & demontre
    * \pre
    * \post
    * \exception     std::logic_error si l'hypothese fournie est vide
    * \exception     std::logic_error si la base de regles est vide
    * \exception     std::logic_error si la base de faits est vide
   */
    std::vector<Regle> SystemeExpert::chainageArriere (const TypeFait & hypothese, bool & demontre)
    {
        //Si aucune hypothese n'est fournie
        if (hypothese.empty()){
            throw std::logic_error("Auncune hypothese passée en argument.");
        }
        //On vérifie ensuite si la base de regles ou de faits est vide
        //Si c'est le cas, on lance un erreur de logic car impossible defaire le chainage avant
        if (baseRegles.empty()){
            throw std::logic_error("Base de règle vide donc impossible de d'effectuer une chainage Arriere. Veuillez recommencer avec une base de règles valide.");
        }
        if (baseFaits.empty()){
            throw std::logic_error("Base de faits vide donc impossible de d'effectuer une chainage arriere. Veuillez recommencer avec une base de faits valide.");
        }
        std::vector<Regle> regles;

        demontre = false;

        //Pour chaque hypothese, on boucle au travers de la base de regle
        for(auto itBaseR = baseRegles.begin(); itBaseR != baseRegles.end(); ++itBaseR)
            //On boucle sur les conclusions de chaque regle
            for(auto itConcl = itBaseR->GetConclusions().begin(); itConcl != itBaseR->GetConclusions().end();++itConcl)
            {
                //On vérifie si l'hypothese est la conclusion actuelle de la regle
                if(*itConcl == hypothese)
                {
                    //Si oui, il faut vérifier que chaque prémisse de cette regle fait partie de notre base de faits
                    //Sinon -> nouvelle hypothese a vérifier
                    //On arrete d'itérer si demontre==true (car on a deja ajouter la regle et les faits de cette regle)
                    for(auto itPrem = itBaseR->GetPremisses().begin(); itPrem != itBaseR->GetPremisses().end() && !demontre; ++itPrem)
                    {
                        auto premisseTrouvee = find(baseFaits.begin(),baseFaits.end(), *itPrem);
                        if(premisseTrouvee == baseFaits.end())
                        {
                            std::vector<tp1::Regle> er1;
                            bool test1;
                            //la premisse ne se trouve pas dans la base de fait, elle devient une hypothese
                            er1 = chainageArriere (*itPrem, test1);
                            if(test1)
                            {
                                //on ajoute toutes les regles dans le vecteur er1 au vecteur regle
                                for(auto itReg = er1.begin();itReg != er1.end();++itReg)
                                {
                                    regles.push_back(*itReg);

                                }
                            }
                        }
                        else
                        {
                            //hypothese verifiee on ajoute la conclusion à la base de faits
                            baseFaits.push_back(*itConcl);
                            //la premisse se trouve dans la base de fait, on peut y ajouter la conclusion
                            regles.push_back(*itBaseR);
                            demontre = true;
                            //break
                        }
                    }
                }
            }
        return regles;
    }
}