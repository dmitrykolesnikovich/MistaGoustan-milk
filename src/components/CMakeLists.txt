set(COMP_SOURCES
		Animator.h
		Animator.cpp
		Script.h
		Script.cpp
		BoxCollider.h
		BoxCollider.cpp
		Sprite.h
		Sprite.cpp
		Velocity.h
		Velocity.cpp)

target_sources(Milk 
	PRIVATE
		${COMP_SOURCES})