/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * osgWorks is (C) Copyright 2009-2011 by Kenneth Mark Bryden
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#ifndef __OSGWTOOLS_COUNT_STATE_SETS_H__
#define __OSGWTOOLS_COUNT_STATE_SETS_H__ 1


#include "osgwTools/Export.h"
#include <osg/NodeVisitor>

#include <string>



namespace osgwTools
{


/** Visitor to count \c StateSet objects, and optionally remove empty \c StateSet objects.
*/
class OSGWTOOLS_EXPORT CountStateSets : public osg::NodeVisitor
{
public:
    /**
    @param removeEmptyStateSets Default: true.
    @param travMode The traversal mode. Default: \c osg::NodeVisitor::TRAVERSE_ALL_CHILDREN.
    */
    CountStateSets( bool removeEmptyStateSets=true, const osg::NodeVisitor::TraversalMode travMode=osg::NodeVisitor::TRAVERSE_ALL_CHILDREN );
    ~CountStateSets();

    /** Sets internal counts to zero. */
    void reset();

    /** Override for base class \c apply() method. */
    virtual void apply( osg::Node& node );
    /** Override for base class \c apply() method. */
    virtual void apply( osg::Geode& node );

    /** Specify whether or not to remove empty \c StateSet objects. Default is true
    (remove empty \c StateSet objects).*/
    void setRemoveEmptyStateSets( bool removeEmptyStateSets );

    /** During traversal, these counters track the total number of programs
    and uniforms removed. They are public so that calling code can access
    them directly following the traversal. */
    unsigned int _uniqueStateSets, _sharedStateSets, _emptyStateSets, _removedStateSets;

protected:
    /** Examines the \c StateSet and increments the unique and shared counters. Also
    increments the empty counter, but doesn't remove it or increment the removed counter.
    The calling \c apply() method is responsible for taking care of that based on the return
    value. Returns true if the \c StateSet is NULL or not empty. Returns false if the
    \c StateSet is non-NULL and empty. */
    bool processStateSet( osg::StateSet* ss );

    bool _removeEmptyStateSets;
};


// osgwTools
}

// __OSGWTOOLS_COUNT_STATE_SETS_H__
#endif