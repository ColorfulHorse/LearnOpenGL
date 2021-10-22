#pragma once
class Renderable {
public:
	virtual void onCreate() = 0;
	virtual void onRender() = 0;
	virtual void onDestroy() = 0;
};
