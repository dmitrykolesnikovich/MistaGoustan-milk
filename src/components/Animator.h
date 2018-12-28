#ifndef _ANIMATOR_
#define _ANIMATOR_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../core/ActorComponent.h"
#include "../utilities/Timer.h"

class Sprite;

struct Animation
{
	Animation(const std::string& n, std::initializer_list<int> f)
	{
		name = n;
		frames = new int[f.size()];

		int i = 0;
		for (auto it : f)
		{
			frames[i] = it;
			++i;
		}

		size = f.size();
	}

	Animation(const std::string& n, std::vector<int> f)
	{
		name = n;
		frames = new int[f.size()];

		int i = 0;
		for (auto it : f)
		{
			frames[i] = it;
			++i;
		}

		size = f.size();
	}

	~Animation()
	{
		delete[] frames;
	}

	std::string name;
	int* frames;
	int size;
};

class Animator : public ActorComponent
{
public:
	static const ComponentType type;

	Animator(Actor& actor);
	~Animator();

	void init();

	void rows(int rows);
	void columns(int columns);

	void togglePaused();

	void addAnimation(const std::string& name, std::initializer_list<int> f);
	void addAnimation(const std::string& name, std::vector<int> f);
	void setAnimation(const std::string& name);

	void update();

private:
	Sprite* sprite_;

	Timer timer_;

	int currentFrame_;
	float timeBetweenFrames_;

	int rows_;
	int columns_;
	int frameWidth_;
	int frameHeight_;

	bool paused_;

	Animation* currentAnimation_;
	std::unordered_map<std::string, std::unique_ptr<Animation>> animations_;
};

#endif
