/*
 * Particle.h
 *
 *  Created on: 31-Dec-2019
 *      Author: KIIT
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace cbh {

class Particle {
private:
	double m_speed;
	double m_direction;

	void init();
public:
	double m_x;
	double m_y;

	Particle();
	virtual ~Particle();
	void update(int interval);
};

} /* namespace cbh */

#endif /* PARTICLE_H_ */
