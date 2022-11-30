#include "construction.hh"


MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();  //the geant4 nist material database

	G4Material *SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2); //defining the silicone dioxide material class
	SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);  //adding the silicone element to the class
	SiO2->AddElement(nist->FindOrBuildElement("O"), 2); //adding the oxygen element to the class

	G4Material *H2O = new G4Material("H2O", 1.000*g/cm3, 2); //defining h20 material class
	H2O->AddElement(nist->FindOrBuildElement("H"), 2); //adding the hydrogen element to class
	H2O->AddElement(nist->FindOrBuildElement("O"), 1); //adding the oxygen element to class

	G4Element *C = nist->FindOrBuildElement("C"); //creating the carbon material class

	G4Material *Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3); //creating the aerogel material class
	Aerogel->AddMaterial(SiO2, 62.5*perCent);  //adding the silione dioxide material to aerogel class
	Aerogel->AddMaterial(H2O, 37.4*perCent);  //adding the h20 material to aergoel class
	Aerogel->AddElement(C, 0.1*perCent);  //adding the carbon material to aerogel class

	G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
	G4double rindexAerogel[2] = {1.1, 1.1};
	G4double rindexWorld[2] = {1.0, 1.0};

	G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
	mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);

	Aerogel->SetMaterialPropertiesTable(mptAerogel);
	
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);

	worldMat->SetMaterialPropertiesTable(mptWorld);

	G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);

	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

	G4Box *solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);

	G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator, Aerogel, "logicRadiator");

	G4VPhysicalVolume *physRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.25*m), logicRadiator, "physRadiator", logicWorld, false, 0, true);

	G4Box *solidDetector = new G4Box("solidDetector", 0.005*m, 0.005*m, 0.01*m);

	logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");

	

	for(G4int i = 0; i < 100; i++)
	{

		for(G4int j = 0; j < 100; j++)
		{
			
			G4VPhysicalVolume *physDetector= new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/100, -0.5*m+(j+0.5)*m/100, 0.49*m), logicDetector, "physDetector", logicWorld, false, j+i*100, true);

		}
	}




	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    if(logicDetector != NULL)
        logicDetector->SetSensitiveDetector(sensDet);
}
	
