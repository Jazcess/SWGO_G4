#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	G4Track *track = aStep->GetTrack();  //creating track object, to 'track' the status of a particle after a'step' (a snapchat of the trajectory)

	track->SetTrackStatus(fStopAndKill); //assigning the track object with the track status

	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();  //the status before the step/snapshot
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint(); //the status after the step/snapshot

	G4ThreeVector posPhoton = preStepPoint->GetPosition(); //getting the position of the photon

	//G4cout << "Photon position: " << posPhoton << G4endl;  //outputting the positon to terminal

	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable(); //creating object on what volumes were 'touched'

	G4int copyNo = touchable->GetCopyNumber(); //retreiving the unique id of volumes that the photons travelled through / hit

	//G4cout << "Copy Number: " << copyNo << G4endl; //outputting these ids to the terminal

	G4VPhysicalVolume *physVol = touchable->GetVolume(); //creating object on what detectors were hit
	G4ThreeVector posDetector = physVol->GetTranslation(); //retreiving the coordinates of the detectors that were hit

	G4cout << "Detector position: " << posDetector << G4endl; //outputting coordinates to the terminal

	return true; //return true, this doesnt really do anything other than satisfying the function output
}
