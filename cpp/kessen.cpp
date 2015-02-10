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
	cout << "�i���̋Z�ŁA�z�𑨂���...�j" << endl;
	cout << "�i�y�[�X�z�����l���Ă������...�i�c��X�^�~�i�F" << energy << "�j�j" << endl;
	cin >> f.energy;
// �c��X�^�~�i�ȏ�̗͂͏o���Ȃ��B //
	if(f.energy >= energy) {
		cout << "�i�S�͂ōs��...�I�j" << endl;
		f.energy = energy;
	}
	energy -= f.energy;
	cout << "�i�z�̋C�z��...�ǂ�����...�j" << endl;
	cin >> f.pos;
	cout << "�������b�I" << endl;
	return f;
}

void Mao::attacked(Force n) {

	if(n.pos == pos) {
		cout << "���̎��ɁA���𕉂킹������...�I" << endl;
		energy -= n.energy * 5;
		pos += rand() % 3 - 1;
		
		if(pos < 1 || pos > 9) {
			cout << "�ǂ��l�߂�ꂽ��...����...�I" << endl;
			pos = rand() % 9;
		} 
	}
	else if(n.pos == pos - 1 || n.pos == pos + 1) {
		cout << "��������ʂ�...�I" << endl;
		energy -= n.energy;
	}
	else {
		cout << "�ǂ���_���Ă���H���������B" << endl;
	}
	if(energy <= 0) {
		energy = 0;
		cout << "���̎����A�s�ꂽ�Ƃ����̂�..." << endl;
	}

}

Game::Game() {

	cout << "����������̎�..." << endl;
	cout << "�s�����A��������I" << endl;
}

void Game::Play() {

	while(h.GetEnergy() > 0) {
		if(m.GetEnergy() <= 0) {
			break;
		}
		cout << "�����F�c��g�o" << m.GetEnergy() << endl;
		m.attacked(h.attack());
	}
	if(m.GetEnergy() > 0) {
		cout << "���O�ȂǁA���̑����ɂ��y�΂ʂ�..." << endl;
		cout << "�o�����Ă��邪�����b�I" << endl;
	}

	Ending();

}

void Game::Ending()const{
	cout << "...�Ƃ����̂��A����p�Y�Ɩ����Ƃ̐킢�̓^����������..." << endl;
}

int main()

{

	srand((unsigned)time(NULL));
	Game g;
	g.Play();
}

