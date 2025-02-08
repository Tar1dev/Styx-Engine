#pragma once

namespace Styx
{
	class Application
	{
	public:
		virtual void init() {}
		virtual void config() {}
		virtual void update(float dt) {}
		virtual void draw() {}
		virtual void shutdown() {}
	};
}