/*
 * Swarm.h
 *
 *  Created on: 31-Dec-2019
 *      Author: KIIT
 */

#include "Particle.h"

#ifndef SWARM_H_
#define SWARM_H_

namespace cbh {

class Swarm {
public:
	const static int NPARTICLES = 5000;
private:
	Particle *m_pParticles;
	int lastTime;
public:
	Swarm();
	virtual ~Swarm();

	const Particle * const getParticles() { return m_pParticles; }
	void update(int elapsed);
};

} /* namespace cbh */

#endif /* SWARM_H_ */
