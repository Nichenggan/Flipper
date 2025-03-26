#pragma warning( disable : 4996 ) 

 
#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include "G2D.h"
using namespace std;

// touche P   : mets en pause
// touche ESC : ferme la fenêtre et quitte le jeu

struct Cible
{
	V2 Pos;
	bool Hit = false;

	// Constructor
	Cible(V2 position, bool hit = false) : Pos(position), Hit(hit) {}
};

struct Rangee
{
	vector<Cible> Cibles;

	// Constructor
	Rangee(const vector<Cible>& cibles) : Cibles(cibles) {}
};

struct Bumper
{
	V2 Pos;
	double r = 40;
	bool Hit = false;
	double T0 = -1;

	// Constructor
	Bumper(V2 position, bool hit = false) : Pos(position), Hit(hit) {}
};

// Rangee initRangee(){
// 	vector<Cible> Cibles = { {V2(100, 100), false}, {V2(200, 100), false}, {V2(300, 100), false}, {V2(400, 100), false}, {V2(500, 100), false} };
// 	return Rangee{Cibles};
// }
///////////////////////////////////////////////////////////////////////////////
//
//    Données du jeu - structure instanciée dans le main

struct GameData
{
	int     idFrame    = 0;
	int     HeightPix  = 800;          // hauteur de la fenêtre de jeu
	int     WidthPix   = 600;          // largeur de la fenêtre de jeu
	V2      BallPos    = V2(300,300 );
	V2      BallMove;
	int     BallRadius = 15;
	int     score	  = 0;

	vector<V2> PreviousPos;  // stocke les dernières positions de la boule
	
	// bords du flipper
	vector<V2> LP{ V2(595, 550), V2(585, 596), V2(542, 638), V2(476, 671), V2(392, 692), V2(300, 700), V2(207, 692),
		V2(123, 671), V2(57, 638), V2(14, 596), V2(5, 550), V2(5,5), V2(595,5), V2(595,550)};

	// cibles
	Rangee R1 = Rangee({ {V2(100, 100), false}, {V2(200, 100), false}, {V2(300, 100), false}, {V2(400, 100), false}, {V2(500, 100), false} });
	// Rangee R1 = Rangee({ {V2(100, 100), false}, {V2(200, 100), false} }); // pour tester

	// Bumpers
	vector<Bumper> bumpers{ {V2(200, 400), false}, {V2(400, 400), false}, {V2(300, 500), false} };


	GameData()
	{
		PreviousPos.resize(50); // stocke les 50 dernières positions connues
		// BallMove = V2(5, 5);   // vecteur déplacement
		BallMove = V2(5, 4);
	}

};

// 0 pas d'intersection
// 1/2/3 intersection entre le segment AB et le cercle de rayon r
int CollisionSegCir(V2 A, V2 B, float r, V2 C)
{
	V2 AB = B - A;
	V2 T = AB;
	T.normalize();
	float d = prodScal(T, C - A);
	if (d > 0 && d < AB.norm())
	{
		V2 P = A + d * T; // proj de C sur [AB]
		V2 PC = C - P;
		if (PC.norm() < r) return 2;
		else               return 0;
	}
	if ((C - A).norm() < r) return 1;
	if ((C - B).norm() < r) return 3;
	return 0;
}

V2 rebond(V2 V, V2 N) {
	if (N.x == 0 && N.y == 0) return V; // Normal vector is zero, no rebound
	N.normalize();
	V2 T = V2(N.y, -N.x);
	float vt = prodScal(V, T);
	float vn = prodScal(V, N);
	return vt * T - vn * N;
}

void testRebond() {
	V2 V(1, -1); // Initial velocity vector
	V2 N(-1, 1); // Normal vector

	V2 result = rebond(V, N);

	std::cout << "Initial velocity: (" << V.x << ", " << V.y << ")" << std::endl;
	std::cout << "Normal vector: (" << N.x << ", " << N.y << ")" << std::endl;
	std::cout << "Rebounded velocity: (" << result.x << ", " << result.y << ")" << std::endl;
}


void UpdatePosAndMove(GameData & G)
{
	V2 P = G.BallPos;
	V2 V = G.BallMove;
	float r = G.BallRadius;
	P = P + V;
	V2 N = V2(0, 0);
	//Collision avec des bords
	for (int i = 0; i < G.LP.size() - 1; i++)
	{
		int c = CollisionSegCir(G.LP[i], G.LP[i + 1], r, P);
		if (c == 2) {
			V2 T = G.LP[i + 1] - G.LP[i];
			V2 Nn= V2(T.y, -T.x);
			Nn.normalize();
			N = N + Nn;
		}
	}
	if (N.x!=0 || N.y!=0) {
		N.normalize();
	}

	//Collision avec des cibles
	for (int i = 0; i < G.R1.Cibles.size(); i++)
	{
		Cible C = G.R1.Cibles[i];
		if (C.Hit) continue; // Skip if already hit
		int c = CollisionSegCir(C.Pos, V2(C.Pos.x, C.Pos.y + 5), r, P);
		if (c == 2) {
			V2 T = V2(C.Pos.x, C.Pos.y + 5) - C.Pos;
			T.normalize();
			N = V2(T.y, -T.x);
			N.normalize();
			G.R1.Cibles[i].Hit = true;
			G.score += 500;
		}
		else if (c == 1) {
			N = P - C.Pos;
			N.normalize();
			G.R1.Cibles[i].Hit = true;
			G.score += 500;


		}
		else if (c == 3) {
			N = C.Pos - P;
			N.normalize();
			G.R1.Cibles[i].Hit = true;
			G.score += 500;

		}
	}

	//Collision avec des bumpers
	for (int i = 0; i < G.bumpers.size(); i++)
	{
		V2 Bpos = G.bumpers[i].Pos;
		if ((P - Bpos).norm() <= r+G.bumpers[i].r) {
			N = P - Bpos;
			N.normalize();
			G.bumpers[i].Hit = true;
			G.bumpers[i].T0 = G2D::elapsedTimeFromStartSeconds();
			G.score += 100;


		}
	}

	V = rebond(V, N);
	G.BallPos = P + V;
	G.BallMove = V;


}



void drawCible(Cible cible, Color color) {
	int thickness = 6; // Thickness of the line
	for (int i = -thickness / 2; i <= thickness / 2; ++i) {
		G2D::drawLine(V2(cible.Pos.x + i, cible.Pos.y), V2(cible.Pos.x + i, cible.Pos.y+5), color);
	}
}


///////////////////////////////////////////////////////////////////////////////
//
// 
//     fonction de rendu - reçoit en paramètre les données du jeu par référence



void render(const GameData & G)
{
    // fond noir	 
	G2D::clearScreen(Color::Black);
	 
	// Titre en haut
	G2D::drawStringFontMono(V2(80, G.HeightPix - 70), string("Score : " + std::to_string(G.score)), 50, 5, Color::Blue);
 
	// la bille
 	G2D::drawCircle(G.BallPos, G.BallRadius, Color::Red, true);
	
	// 3 bumpers
	for (Bumper B : G.bumpers)
	{

		if (G2D::elapsedTimeFromStartSeconds() - B.T0 < 1) {
			G2D::drawCircle(B.Pos, (1 - (G2D::elapsedTimeFromStartSeconds() - B.T0))*10 + B.r, Color::Red, true);
		}
		G2D::drawCircle(B.Pos, B.r, Color::Blue, true);
	}

	// cibles
	for(Cible C : G.R1.Cibles)
	{
		if (C.Hit)
			drawCible(C, Color::Red);
		else
			drawCible(C, Color::Green);
	}






	// les bords

	for (int i = 0; i < G.LP.size()-1; i++)
	   G2D::drawLine(G.LP[i],G.LP[i+1], Color::Green);

	// les positions précédentes

	for (V2 P : G.PreviousPos)
		G2D::setPixel(P, Color::Green);

	// précise que l'on est en pause

	if ( G2D::isOnPause() )
		G2D::drawStringFontMono(V2(100, G.HeightPix / 2), string("Pause..."), 50, 5, Color::Yellow);

	// envoie les tracés à l'écran

	G2D::Show();
}

	
///////////////////////////////////////////////////////////////////////////////
//
//
//      Gestion de la logique du jeu - reçoit en paramètre les données du jeu par référence

void UpdateRangee(GameData & G, Rangee & r) {
	bool fini = true;
	for(Cible C : r.Cibles)
	{
		if (!C.Hit) {
			fini = false;
		}
	}
	if (fini) {
		G.score += 1111;
		for(int i = 0; i < r.Cibles.size(); i++)
		{
			r.Cibles[i].Hit = false;
		}
	}
}

void Logic(GameData & G) // appelé 20 fois par seconde
{
	G.idFrame += 1;

	UpdatePosAndMove(G);
	UpdateRangee(G, G.R1);

  
	G.PreviousPos.push_back(G.BallPos);
	G.PreviousPos.erase(G.PreviousPos.begin());
	 
}
 

///////////////////////////////////////////////////////////////////////////////
//
//
//        Démarrage de l'application



int main(int argc, char* argv[])
{
	testRebond();
	GameData G;   // instanciation de l'unique objet GameData qui sera passé aux fonctions render et logic

	G2D::initWindow(V2(G.WidthPix, G.HeightPix), V2(200, 200), string("Super Flipper 600 !!"));

	int callToLogicPerSec = 50;  // si vous réduisez cette valeur => ralentit le jeu

	G2D::Run(Logic, render, G, callToLogicPerSec,true);


}





