#pragma once
#include<vector>
#include"BARRIER.h"

enum INVADER_TYPE {
	INVADER_NORMAL,
	INVADER_FAST   
};

class INVADER {
	float x, y;
	float dir;
	bool alive;
	int img;
	int scoreValue = 100;
	int type;
	int direction;

public:
	void set(float x, float y, int image, float dir);
	void update(float dx);
	void draw();
	void moveDown();
	void reverseDir();
	void setScore(int s) { scoreValue = s; }
	int getScore() const { return scoreValue; }
	bool checkHit(float bx, float by);
	bool isAlive() const;
	void kill();
	float getX() const;
	float getY() const;
};