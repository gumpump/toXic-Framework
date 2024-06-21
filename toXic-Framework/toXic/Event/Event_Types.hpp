#ifndef EVENT_TYPES_IS_DEFINED
#define EVENT_TYPES_IS_DEFINED

#define tX_EVENT_NO_TYPE -1

struct tX_Event
{
	int Type;
	void *Data;
	int Length;
};

#endif