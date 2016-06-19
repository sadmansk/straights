/*
* Observer class.  Abstract class for Observer Pattern
*
*
*  Created by Jo Atlee on 06/07/09.
*  Copyright 2009 UW. All rights reserved.
*
*/


#ifndef OBSERVER_H_
#define OBSERVER_H_

class Subject;


class Observer {
public:
	virtual void update () = 0;
};


#endif // OBSERVER_H_
