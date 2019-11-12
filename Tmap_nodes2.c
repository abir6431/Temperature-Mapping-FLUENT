/**********************************************************************
   UDF to produce temperature Mapping for Structural Analysis
   This UDF produces temperature map on surface faces and cell centroids
   
 ***********************************************************************/
#include "udf.h"
#include "prf.h" /*this is header needed for global reduction operator (check FLUENT customization manual 7.5.4. Global Reduction Macros) */

void loop_over_zones_faces(int IDs[],int IDlen);              /*loop over zones function for faces*/
void loop_over_zones_cell(int IDs[],int IDlen);      /*loop over zones function for cells*/


/************************************************************************
                       This portion is for cell
 ***********************************************************************/
 
DEFINE_ON_DEMAND(coor_vs_temp_cells)
{
	#if !RP_HOST            /*host has no mesh data so it must be excluded (see 7.5.1 FLUENT customization manual)*/
  	int zone_ID[]={113};	/*Lookup_Thread macro will look over the zone IDs provided in this array*/
   	int ID_len=sizeof(zone_ID)/sizeof(int);	/*This finds the length of the zone_ID[] array*/
   	loop_over_zones_cell(zone_ID,ID_len);
	#endif				/*excludes the HOST PROCESS :: end*/
}

void loop_over_zones_cell(int zoneID[],int IDlen)
{ 
    Domain *d=Get_Domain(1); /* declare domain pointer since it is not passed as an argument to the DEFINE macro. The domain argument provides access to all cell and face threads in the mesh. used to retrieve a domain
                              pointer when it is not explicitly passed as argument to your UDF (i.e DEFINE_ON_DEMAND macro has no arg). See 3.2.6.3. Loop over all cell threads in the domain */

    cell_t c;
    real x[ND_ND];      /*this holds the position vector.....see Section 8.1.3. of FLUENT Customization Manual*/
    int i;
    for (i=0;i<IDlen;i++)		/*the for loop will loop over each zone_ID element*/
    {
        Thread *t=Lookup_Thread(d,zoneID[i]);	/*lookup the thread IDs in zone_ID*/
        begin_c_loop_int(c,t)
        {   
            C_CENTROID(x,c,t);
            Message("\n %.4f, %.4f, %.4f, %.3f",x[0],x[1],x[2],C_T(c,t));
	    }
        end_c_loop_int(c,t)
     }
}
/************************************************************************
                        This portion is for face
************************************************************************/

/*REMEMBER FOR FACE TEMPERATURES WHILE USING F_T(f,t) YOU MUST USE ZONE_ID TO LOOP OVER THREADS. USING thread_loop_f(t,d) TO LOOP OVER THREADS WILL GIVE SEGMENTATION FAULT IN FLUENT*/
DEFINE_ON_DEMAND(coor_vs_temp_face)
{
	#if !RP_HOST            /*host has no mesh data so it must be excluded (see 7.5.1 FLUENT customization manual)*/
  	int zone_ID[]={1632,1608};	/*Lookup_Thread macro will look over the zone IDs provided in this array*/
   	int ID_len=sizeof(zone_ID)/sizeof(int);	/*This finds the length of the zone_ID[] array*/
   	loop_over_zones_faces(zone_ID,ID_len);
	#endif				/*excludes the HOST PROCESS :: end*/
}

void loop_over_zones_faces(int zoneID[],int IDlen)
{ 
    Domain *d=Get_Domain(1); /* declare domain pointer since it is not passed as an argument to the DEFINE macro. The domain argument provides access to all cell and face threads in the mesh. used to retrieve a domain
                              pointer when it is not explicitly passed as argument to your UDF (i.e DEFINE_ON_DEMAND macro has no arg). See 3.2.6.3. Loop over all cell threads in the domain */
    face_t f;
    real x[ND_ND];      /*this holds the position vector.....see Section 8.1.3. of FLUENT Customization Manual*/
    int i;
    for (i=0;i<IDlen;i++)		/*the for loop will loop over each zone_ID element*/
    {
        Thread *t=Lookup_Thread(d,zoneID[i]);	/*lookup the thread IDs in zone_ID*/
        
            begin_f_loop_int(f,t)
            if PRINCIPAL_FACE_P(f,t)        /*face is in the principal compute node*/

            {
                F_CENTROID(x,f,t);
                Message("\n %.4f, %.4f, %.4f, %.3f",x[0],x[1],x[2],F_T(f,t));
            }
            end_f_loop_int(f,t)
    }
}


