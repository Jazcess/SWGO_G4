#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable(); //retrieving the geant4 particle table
	G4String particleName="proton"; //assigning particle name
	G4ParticleDefinition *particle = particleTable->FindParticle("proton"); //finding particle in table

	G4ThreeVector pos(0., 0., 0.); //setting particle initial position
	G4ThreeVector mom(0., 0., 1.); //setting particle initial momentum

	fParticleGun->SetParticlePosition(pos); //adding properites to particle gun object
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleMomentum(100.*GeV);
	fParticleGun->SetParticleDefinition(particle);

	fParticleGun->GeneratePrimaryVertex(anEvent); //generate an event from particle gun
}

