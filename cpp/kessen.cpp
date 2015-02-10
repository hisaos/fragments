#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

class Hero;
class Mao;

class Force {
	friend class Hero;
	friend class Mao;
	int energy;
	int pos;
};

class Hero {

	int energy;
public:
	Hero():energy(50){}
	Force attack();
	int GetEnergy() const { return energy; }
};

class Mao {

	int energy;
	int pos;
public:
	Mao():energy(100), pos(rand() % 10) {}
	void attacked(Force n);
	int GetEnergy() const{ return energy; }

};

class Game {

	Hero h;
	Mao m;
	void Ending()const;
public:
	Game();
	void Play();
};

Force Hero::attack() {

	Force f;
	cout << endl;
	cout << "（この技で、奴を捉える...）" << endl;
	cout << "（ペース配分も考えていかんと...（残りスタミナ：" << energy << "））" << endl;
	cin >> f.energy;
// 残りスタミナ以上の力は出せない。 //
	if(f.energy >= energy) {
		cout << "（全力で行く...！）" << endl;
		f.energy = energy;
	}
	energy -= f.energy;
	cout << "（奴の気配は...どっちに...）" << endl;
	cin >> f.pos;
	cout << "そこだッ！" << endl;
	return f;
}

void Mao::attacked(Force n) {

	if(n.pos == pos) {
		cout << "この私に、傷を負わせただと...！" << endl;
		energy -= n.energy * 5;
		pos += rand() % 3 - 1;
		
		if(pos < 1 || pos > 9) {
			cout << "追い詰められたか...くっ...！" << endl;
			pos = rand() % 9;
		} 
	}
	else if(n.pos == pos - 1 || n.pos == pos + 1) {
		cout << "避けきれぬか...！" << endl;
		energy -= n.energy;
	}
	else {
		cout << "どこを狙っている？こっちだ。" << endl;
	}
	if(energy <= 0) {
		energy = 0;
		cout << "この私が、敗れたというのか..." << endl;
	}

}

Game::Game() {

	cout << "今こそ決戦の時..." << endl;
	cout << "行くぞ、魔王よっ！" << endl;
}

void Game::Play() {

	while(h.GetEnergy() > 0) {
		if(m.GetEnergy() <= 0) {
			break;
		}
		cout << "魔王：残りＨＰ" << m.GetEnergy() << endl;
		m.attacked(h.attack());
	}
	if(m.GetEnergy() > 0) {
		cout << "お前など、私の足元にも及ばぬわ..." << endl;
		cout << "出直してくるがいいッ！" << endl;
	}

	Ending();

}

void Game::Ending()const{
	cout << "...というのが、ある英雄と魔王との戦いの顛末だそうだ..." << endl;
}

int main()

{

	srand((unsigned)time(NULL));
	Game g;
	g.Play();
}

