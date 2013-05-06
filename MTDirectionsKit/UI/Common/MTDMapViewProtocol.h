//
//  MTDMapView.h
//  MTDirectionsKit
//
//  Created by Matthias Tretter on 06.05.13.
//  Copyright (c) 2013 Matthias Tretter (@myell0w). All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MTDDirectionsRouteType.h"
#import "MTDDirectionsRequestOption.h"


@class MTDWaypoint;
@class MTDDirectionsOverlay;
@class MTDDirectionsOverlayView;
@class MTDRoute;

@protocol MTDMapView <NSObject>

/******************************************
 @name Directions
 ******************************************/

/**
 The current active direction overlay. Setting the directions overlay automatically removes
 the previous directionsOverlay (if existing) and adds the new directionsOverlay as an overlay
 to the underlying MKMapView.
 */
@property (nonatomic, strong) MTDDirectionsOverlay *directionsOverlay;

/**
 Starts a request and loads the directions between the specified coordinates.
 When the request is finished the directionsOverlay gets set on the MapView and
 the region gets zoomed (animated) to show the whole overlay, if the flag zoomToShowDirections is set.

 @param fromCoordinate the start point of the direction
 @param toCoordinate the end point of the direction
 @param routeType the type of the route requested, e.g. pedestrian, cycling, fastest driving
 @param zoomToShowDirections flag whether the mapView gets zoomed to show the overlay (gets zoomed animated)

 @see loadDirectionsFromAddress:toAddress:routeType:zoomToShowDirections:
 @see loadDirectionsFrom:to:intermediateGoals:routeType:options:zoomToShowDirections:
 @see loadAlternativeDirectionsFrom:to:routeType:zoomToShowDirections:
 @see cancelLoadOfDirections
 */
- (void)loadDirectionsFrom:(CLLocationCoordinate2D)fromCoordinate
                        to:(CLLocationCoordinate2D)toCoordinate
                 routeType:(MTDDirectionsRouteType)routeType
      zoomToShowDirections:(BOOL)zoomToShowDirections;

/**
 Starts a request and loads the directions between the specified addresses.
 When the request is finished the directionsOverlay gets set on the MapView and
 the region gets zoomed (animated) to show the whole overlay, if the flag zoomToShowDirections is set.

 @param fromAddress the address of the starting point of the route
 @param toAddress the addresss of the end point of the route
 @param routeType the type of the route requested, e.g. pedestrian, cycling, fastest driving
 @param zoomToShowDirections flag whether the mapView gets zoomed to show the overlay (gets zoomed animated)

 @see loadDirectionsFrom:to:routeType:zoomToShowDirections:
 @see loadDirectionsFrom:to:intermediateGoals:routeType:options:zoomToShowDirections:
 @see loadAlternativeDirectionsFrom:to:routeType:zoomToShowDirections:
 @see cancelLoadOfDirections
 */
- (void)loadDirectionsFromAddress:(NSString *)fromAddress
                        toAddress:(NSString *)toAddress
                        routeType:(MTDDirectionsRouteType)routeType
             zoomToShowDirections:(BOOL)zoomToShowDirections;

/**
 Deprecated, use loadDirectionsFrom:to:intermediateGoals:routeType:options:zoomToShowDirections: instead.

 Starts a request and loads the directions between the specified start and end waypoints while
 travelling to all intermediate goals along the route. When the request is finished the
 directionsOverlay gets set on the MapView and the region gets zoomed (animated) to show the
 whole overlay, if the flag zoomToShowDirections is set.

 @param from the starting waypoint of the route
 @param to the end waypoint of the route
 @param intermediateGoals an optional array of waypoint we want to travel to along the route
 @param optimizeRoute a flag that indicates whether the route shall get optimized if there are intermediate goals.
 if YES, the intermediate goals can get reordered to guarantee a fast route traversal
 @param routeType the type of the route requested, e.g. pedestrian, cycling, fastest driving
 @param zoomToShowDirections flag whether the mapView gets zoomed to show the overlay (gets zoomed animated)

 @see loadDirectionsFrom:to:routeType:zoomToShowDirections:
 @see loadDirectionsFromAddress:toAddress:routeType:zoomToShowDirections:
 @see loadAlternativeDirectionsFrom:to:routeType:zoomToShowDirections:
 @see cancelLoadOfDirections
 */
- (void)loadDirectionsFrom:(MTDWaypoint *)from
                        to:(MTDWaypoint *)to
         intermediateGoals:(NSArray *)intermediateGoals
             optimizeRoute:(BOOL)optimizeRoute
                 routeType:(MTDDirectionsRouteType)routeType
      zoomToShowDirections:(BOOL)zoomToShowDirections  __attribute__((deprecated));

/**
 Starts a request and loads the directions between the specified start and end waypoints while
 travelling to all intermediate goals along the route. When the request is finished the
 directionsOverlay gets set on the MapView and the region gets zoomed (animated) to show the
 whole overlay, if the flag zoomToShowDirections is set.

 @param from the starting waypoint of the route
 @param to the end waypoint of the route
 @param intermediateGoals an optional array of waypoint we want to travel to along the route
 @param routeType the type of the route requested, e.g. pedestrian, cycling, fastest driving
 @param options mask of options that can be specified on the request, e.g. optimization of the route, avoiding toll roads etc.
 @param zoomToShowDirections flag whether the mapView gets zoomed to show the overlay (gets zoomed animated)

 @see loadDirectionsFrom:to:routeType:zoomToShowDirections:
 @see loadDirectionsFromAddress:toAddress:routeType:zoomToShowDirections:
 @see loadAlternativeDirectionsFrom:to:routeType:zoomToShowDirections:
 @see cancelLoadOfDirections
 */
- (void)loadDirectionsFrom:(MTDWaypoint *)from
                        to:(MTDWaypoint *)to
         intermediateGoals:(NSArray *)intermediateGoals
                 routeType:(MTDDirectionsRouteType)routeType
                   options:(MTDDirectionsRequestOptions)options
      zoomToShowDirections:(BOOL)zoomToShowDirections;

/**
 Starts a request and loads maximumNumberOfAlternatives different routes between the
 specified start and end waypoints. When the request is finished the directionsOverlay gets set
 on the MapView and the region gets zoomed (animated) to show the whole overlay, if the flag
 zoomToShowDirections is set.

 @param from the starting waypoint of the route
 @param to the end waypoint of the route
 @param routeType the type of the route requested, e.g. pedestrian, cycling, fastest driving
 @param zoomToShowDirections flag whether the mapView gets zoomed to show the overlay (gets zoomed animated)

 @see loadDirectionsFrom:to:routeType:zoomToShowDirections:
 @see loadDirectionsFromAddress:toAddress:routeType:zoomToShowDirections:
 @see loadDirectionsFrom:to:intermediateGoals:routeType:options:zoomToShowDirections:
 @see cancelLoadOfDirections
 */
- (void)loadAlternativeDirectionsFrom:(MTDWaypoint *)from
                                   to:(MTDWaypoint *)to
                            routeType:(MTDDirectionsRouteType)routeType
                 zoomToShowDirections:(BOOL)zoomToShowDirections;

/**
 Cancels a possible ongoing request for loading directions.
 Does nothing if there is no request active.

 @see loadDirectionsFrom:to:routeType:zoomToShowDirections:
 */
- (void)cancelLoadOfDirections;

/**
 Removes the currenty displayed directionsOverlay view from the MapView,
 if one exists. Does nothing otherwise.
 */
- (void)removeDirectionsOverlay;

/**
 If multiple routes are available, selects the active route.
 The delegate will be called as if the user had changed the active route by tapping on it

 @param route the new active route
 */
- (void)activateRoute:(MTDRoute *)route;

/******************************************
 @name Inter-App
 ******************************************/

/**
 If directionsOverlay is currently set, this method opens the same directions
 that are currently displayed on top of your MTDMapView in the built-in Maps.app
 of the user's device. Does nothing otherwise.

 @return YES in case the directionsOverlay is currently set and the Maps App was opened, NO otherwise
 */
- (BOOL)openDirectionsInMapsApp;

/******************************************
 @name Region
 ******************************************/

/**
 Sets the region of the MapView to show the whole directionsOverlay at once.

 @param animated flag whether the region gets changed animated, or not
 */
- (void)setRegionToShowDirectionsAnimated:(BOOL)animated;

@end
