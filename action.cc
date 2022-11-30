#include "action.hh"

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build() const
{
	//making a generator
	MyPrimaryGenerator *generator = new MyPrimaryGenerator();
	SetUserAction(generator);
}
