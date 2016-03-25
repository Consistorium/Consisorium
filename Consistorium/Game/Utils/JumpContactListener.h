#include <Box2D\Box2D.h>

class JumpContactListener : public b2ContactListener
{
private:
	int footContactsCount_;
public:
	JumpContactListener();
	~JumpContactListener();

	void BeginContact(b2Contact* contact);

	void EndContact(b2Contact* contact);

	int getContactsCount();
};