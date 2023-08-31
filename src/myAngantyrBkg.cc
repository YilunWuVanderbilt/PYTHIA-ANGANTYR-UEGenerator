#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/HepMC2.h"
#include <HepMC/GenEvent.h>

using namespace Pythia8;

bool isParticleInRanges(const Particle& particle, double minPt, double minEta, double maxEta) {
    if (particle.isFinal()) {  // Only consider final-state particles
        double pt = particle.pT();
        double eta = particle.eta();
        return (pt >= minPt && eta >= minEta && eta <= maxEta);
    }
    return false;
}

int main(int argc, char* argv[]) {

    // Rest of your code...

    // Interface for conversion from Pythia8::Event to HepMC event.
    // Specify file where HepMC events will be stored.
    HepMC::IO_GenEvent output(argv[2], std::ios::out);
    
    // Generator.
    Pythia pythia;

    // Read in commands from external file.
    pythia.readFile(argv[1]);
    int seed = std::stoi(argv[3]);
    
    pythia.readString("Random:seed = " + std::to_string(seed));
    
    // Initialization.
    pythia.init();
    
    int nEvent = pythia.mode("Main:numberOfEvents");
    
    // Begin event loop.
    for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
        if (!pythia.next()) continue;
        if (pythia.info.hiInfo->b() > 4.3) continue;
        
        // Create an instance of IO_GenEvent to write the events
        HepMC::GenEvent* genEvent = new HepMC::GenEvent();
        
        // Create a new HepMC vertex for the event.
        HepMC::GenVertex* vertex = new HepMC::GenVertex();
        
        // Filter particles based on desired pT, eta, and phi ranges.
        for (int i = 0; i < pythia.event.size(); ++i) {
            const Particle& particle = pythia.event[i];
            if (isParticleInRanges(particle, 0.55, -3., 3)) {
                HepMC::GenParticle* genParticle = new HepMC::GenParticle(
                    HepMC::FourVector(particle.px(), particle.py(), particle.pz(), particle.e()),
                    particle.id(),
                    //particle.status()
                    1  // Set the desired status code to 1 because later DELPHES only takes "1" as final particles status
                );
                
                // Associate the particle with the vertex.
                vertex->add_particle_out(genParticle);
                if (i == 2000) {
                    break;
                }
            }
        }
        
        // Set the units for the HepMC event.
        genEvent->use_units(HepMC::Units::GEV, HepMC::Units::MM);
        
        // Add the vertex to the event.
        genEvent->add_vertex(vertex);
        
        // Write the HepMC event to the output file.
        output.write_event(genEvent);
        
        //delete hepmcEvent;
        delete vertex;
        genEvent->clear();
    }

    return 0;
}
