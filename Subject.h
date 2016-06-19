/*
 * MVC example of GTKmm program
 *
 * Subject class.  Abstract class for Observer Pattern
 *
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#ifndef SUBJECT_H_
#define SUBJECT_H_

#include <set>

class Observer;

class Subject {
public:
       void subscribe( Observer* );
       void unsubscribe( Observer* );

protected:
       void notify();

private:
       typedef std::set< Observer* > Observers;
       Observers observers_;
}; // Subject


#endif // SUBJECT_H_
