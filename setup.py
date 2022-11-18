import os
import requests
import tarfile

path = '/home/j/jss55/Software/geant4/geant4-v11.0.3'

exists = os.path.exists(path)

if exists != True:

	os.system('''
	mkdir Software
	cd Software
	mkdir geant4
	cd geant4
	''')
	
	url = 'https://cern.ch/geant4-data/releases/geant4-v11.0.3.tar.gz'
	response = requests.get(url)
	open("/home/j/jss55/Software/geant4/geant4-v11.0.3.tar.gz", "wb").write(response.content)

	tar = tarfile.open("/home/j/jss55/Software/geant4/geant4-v11.0.3.tar.gz")
	tar.extractall("/home/j/jss55/Software/geant4/")
	tar.close()
	os.remove("/home/j/jss55/Software/geant4/geant4-v11.0.3.tar.gz")

