#include<bits/stdc++.h>
using namespace std;


struct Character
{
    //User inputted stats :-
    double atk=1000;
    double em=40;
    double hp=15000;
    double def=800;
    double er=120;
    double dmg;
    double cr;
    double cdmg;

    //Database stat( lvl 90 character , lvl 90 hilichurl enemy ) :-
    double baseatk;
    double basehp;
    double basedef;
    double resMult=0.9;
    double defMult=0.5;
    double lvlMult=1446.853;

    // Anemo character infusion
    double infusiondmg=0;
    double infusiontalent=0;
    double infusionresMult=1.15;

    //Skill dmg
    double skilltalent=0;
    double skilldmg=0;

    //Burst dmg
    double bursttalent=0;
    double burstdmg=0;
};

void WelcomeMessage()
{
    cout<<"\nWelcome to GENSHIN TC \n";
}

void GetStats(Character * c,bool atk,bool em,bool hp,bool def,bool er)
{
    if(atk)
    {
        cout<<"Enter ATK : ";
        cin>>c->atk;
    }

    if(em)
    {
        cout<<"Enter EM : ";
        cin>>c->em;
    }

    if(hp)
    {
        cout<<"Enter HP : ";
        cin>>c->hp;
    }

    if(def)
    {
        cout<<"Enter DEF : ";
        cin>>c->def;
    }

    if(er)
    {
        cout<<"Enter ER : ";
        cin>>c->er;
    }

    cout<<"Enter DMG% : ";
    cin>>c->dmg;

    cout<<"Enter CR% : ";
    cin>>c->cr;

    cout<<"Enter CDMG% : ";
    cin>>c->cdmg;
}

double swirl(Character c)
{
    // Assumes 4 VV active

    double incomingdmg = 0.6 * c.lvlMult * ( 1 + 0.6 + ((16*c.em)/(c.em+2000)) );
    double outgoingdmg = incomingdmg * c.infusionresMult;
    return outgoingdmg;
}

double overload(Character c)
{
    //Assumes no overload buff
    if(c.resMult>1)
        c.resMult=1+(c.resMult-1)/2;

    double incomingdmg = 2 * c.lvlMult * ( 1 + ((16*c.em)/(c.em+2000)) );
    double outgoingdmg = incomingdmg * c.resMult;
    return outgoingdmg;
}

double dmg(Character c,double basedmg,double dmg,double resMult)
{
    if(c.cr>100)
        c.cr=100;
    if(c.cr<0)
        c.cr=0;
    if(resMult>1)
        resMult=1+(resMult-1)/2;

    double incomingdmg = basedmg * (1+dmg/100) * (1+(c.cr/100)*(c.cdmg/100));
    double outgoingdmg = incomingdmg * resMult * c.defMult ;
    return outgoingdmg;
}

double edmg(Character c,double basedmg)
{
    return dmg(c,basedmg,c.skilldmg,c.resMult);
}

double qdmg(Character c,double basedmg)
{
    return dmg(c,basedmg,c.burstdmg,c.resMult);
}

double infusedmg(Character c,double basedmg)
{
    return dmg(c,basedmg,c.infusiondmg,c.infusionresMult);
}



// CHARACTERS BELOW


//VENTI
void venti()
{
    Character venti;
    
    GetStats(&venti,1,1,0,0,0);

    // Character Stats( lvl 90 , skill 8 , burst 8 , Weapon=Stringless(510))

    venti.baseatk=263+510;
    venti.basedef=669;
    venti.basehp=10531;
    venti.skilltalent=441.6;
    venti.bursttalent=60.16;
    venti.infusiontalent=30.08;


    // TEAM

    cout<<"Enter team name : ";
    string comp;
    cin>>comp;
    if(comp=="morgana")
    {
        //MORGANA ( Weapon=Stringless , Artifact = 4VV( 15% dmg) , Resonance=2 CRYO( 15% cr) ; Buffs= 20%cryodmg( ganyu ) , 50%dmg%( mona ) )

        venti.cr+=15;
        venti.infusiondmg+=48+20+50;
        venti.skilldmg+=venti.dmg+48+15+50;
        venti.burstdmg+=venti.dmg+48+15+50;

        // Assume aoe, 18 swirls total

        double reactiondmg = 2 * (2+7) * swirl(venti);
        double skilldmg = 2 * edmg ( venti , venti.atk*venti.skilltalent/100 );
        double burstdmg = 1 * (18) * qdmg ( venti ,venti.atk*venti.bursttalent/100 );
        double infusiondmg = 1 * (18) * infusedmg ( venti , venti.atk*venti.infusiontalent/100 );

        double totaldmg=reactiondmg+skilldmg+burstdmg+infusiondmg;

        cout<<"\n DAMAGE = "<<totaldmg<<"\n\n";
    }
    else
    {
        cout<<"No such team exists";
    }
    
}



//Xiangling
void xiangling()
{
    Character xiangling;
    
    GetStats(&xiangling,1,1,0,0,1);

    // Character Stats( lvl 90 , skill 11 , burst 11 , Weapon=Catch(510))

    xiangling.baseatk=225+510;
    xiangling.basedef=669;
    xiangling.basehp=10875;
    xiangling.skilltalent=211.43;
    xiangling.bursttalent=200; //averaged approx


    // TEAM

    cout<<"Enter team name : ";
    string comp;
    cin>>comp;
    if(comp=="rational")
    {
        //RATIONAL ( Weapon=Catch , Artifact = 4Emblem , Resonance=2 PYRO(25% atk) ; Buffs= 23.2%burstdmg( raiden ) ,-921atk( bennett ) , -5% PyroRes( xiangling ) )

        xiangling.cr+=11.5; //averaged approx
        xiangling.skilldmg+=xiangling.dmg;
        xiangling.burstdmg+=xiangling.dmg+32+0.2*xiangling.er+23.2;
        xiangling.atk+=xiangling.baseatk*0.25; //Assumes stats were taken when xiangling stats dont include buffs
        xiangling.resMult+=0.08; //averaged approx

        // Assume single target, 14 overloads, 90% burst vaporise , 50% skill vaporise

        double reactiondmg = 16 * overload(xiangling);
        double vaporiseMult= 1.5 * (1 + (2.78 * xiangling.em/(xiangling.em+1400)));
        double skilldmg = 4 * edmg ( xiangling , xiangling.atk*xiangling.skilltalent/100 ) * ( 0.5 * vaporiseMult + 0.5 );
        double burstdmg = 14 * qdmg ( xiangling ,xiangling.atk*xiangling.bursttalent/100 ) * ( 0.9 * vaporiseMult + 0.1 );
        double totaldmg=reactiondmg+skilldmg+burstdmg;

        cout<<"\n DAMAGE = "<<totaldmg<<"\n\n";
    }
    else if(comp=="yelanrational")
    {
        // C0 Yelan assumed
        //YELANRATIONAL ( Weapon=Catch , Artifact = 4Emblem , Resonance=2 PYRO(25% atk) ; Buffs= , 20%atk( yelan-elegy ) , 100em( yelan-elegy) , 23.2%burstdmg( raiden ) ,-921atk( bennett ) , -5% PyroRes( xiangling ) )

        xiangling.cr+=11.5; //averaged approx
        xiangling.skilldmg+=xiangling.dmg;
        xiangling.burstdmg+=xiangling.dmg+32+0.2*xiangling.er+23.2;
        xiangling.atk+=xiangling.baseatk*(0.2+0.25); //Assumes stats were taken when xiangling stats dont include buffs
        xiangling.resMult+=0.08; //averaged approx
        xiangling.em+=100;

        // Assume single target, 14 overloads, 75% burst vaporise , 40% skill vaporise

        double reactiondmg = 16 * overload(xiangling);
        double vaporiseMult= 1.5 * (1 + (2.78 * xiangling.em/(xiangling.em+1400)));
        double skilldmg = 4 * edmg ( xiangling , xiangling.atk*xiangling.skilltalent/100 ) * ( 0.4 * vaporiseMult + 0.6 );
        double burstdmg = 14 * qdmg ( xiangling ,xiangling.atk*xiangling.bursttalent/100 ) * ( 0.75 * vaporiseMult + 0.25 );
        double totaldmg=reactiondmg+skilldmg+burstdmg;

        cout<<"\n DAMAGE = "<<totaldmg<<"\n\n";
    }
    else
    {
        cout<<"No such team exists";
    }
}




void CheckCharacter(string s)
{
    if(s=="venti")
        venti();
    else if(s=="xiangling")
        xiangling();
    else
        cout<<"This character has no TC yet";
}



void ChooseCharacter()
{
    cout<<"Enter Character Name : ";
    string CharacterName;
    cin>>CharacterName;

    CheckCharacter(CharacterName);
}



int main()
{
    WelcomeMessage();

    ChooseCharacter();

    return 0;
}