class CfgVehicles {
    class Man;
    class CAManBase: Man {
        class ACE_SelfActions {
            class ACE_Equipment {
                class GVAR(place) {
                    displayName = CSTRING(Placedown);
                    condition = QUOTE([ARR_2(_player,'ACE_Tripod')] call EFUNC(common,hasItem));
                    statement = QUOTE([ARR_2(_player,'ACE_Tripod')] call FUNC(place));
                    showDisabled = 0;
                    priority = 2;
                    icon = PATHTOF(UI\w_sniper_tripod_ca.paa);
                };
            };
        };
    };

    class Item_Base_F;
    class ACE_Item_Tripod: Item_Base_F {
		author[] = {"Rocko", "Scubaman3D"};
        scope = 2;
        scopeCurator = 2;
        displayName = CSTRING(DisplayName);
        vehicleClass = "Items";
        class TransportItems {
            class ACE_Tripod {
                name = "ACE_Tripod";
                count = 1;
            };
        };
    };

    class Box_NATO_Support_F;
    class ACE_Box_Misc: Box_NATO_Support_F {
        class TransportItems {
            MACRO_ADDITEM(ACE_Tripod,2);
        };
    };
    
    class thingX;
    class ACE_TripodObject: thingX {
        XEH_ENABLED;
        scope = 2;
        displayName = CSTRING(DisplayName);
        model = PATHTOF(data\sniper_tripod.p3d);
        class AnimationSources {
            class slide_down_tripod {
                source = "user";
                animPeriod = 0.02;
                initPhase = 0;
                minValue = 0;
                maxValue = 1;			
            };
            class retract_leg_1: slide_down_tripod {};
            class retract_leg_2: retract_leg_1 {};
            class retract_leg_3: retract_leg_2 {};
        };
        EGVAR(dragging,canDrag) = 1;
        EGVAR(dragging,dragPosition[]) = {0,1,0};
        EGVAR(dragging,dragDirection) = 0;
        class ACE_Actions {
            class ACE_MainActions {
                selection = "";
                distance = 5;
                condition = "true";
                class ACE_Pickup {
                    selection = "";
                    displayName = CSTRING(PickUp);
                    distance = 5;
                    condition = "true";
                    statement = QUOTE([ARR_2(_target,_player)] call FUNC(pickup));
                    showDisabled = 0;
                    exceptions[] = {};
                    priority = 5;
                    icon = PATHTOF(UI\w_sniper_tripod_ca.paa);
                };
                class ACE_Adjust {
                    selection = "";
                    displayName = CSTRING(Adjust);
                    distance = 5;
                    condition = "true";
                    statement = QUOTE(_target call FUNC(adjust));
                    showDisabled = 0;
                    exceptions[] = {};
                    priority = 5;
                    icon = PATHTOF(UI\w_sniper_tripod_ca.paa);
                };
            };
        };
    };
};
