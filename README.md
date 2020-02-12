# Temperature-Mapping-FLUENT
Temperature Mapping from ANSYS FLUENT

This Project has 2 files:

A. UDF file: Tmap_nodes2.c
  The UDF file (Tmap_nodes2.c)  will enable user to generate temperature data at every 'face' and 'cell' centroids for any specified 
  'Zone' from ANSYS FLUENT.

  Guidelines:
  The user only needs to provide the "ZONE ID" for the zones for which he seeks the Temperature mapping data. There are two places in the   UDF (Tmap_nodes2.c) where this data should be provided.
  1. Line 20 for 'cells'.
  2. Line 53 for 'faces'.
  In case there are multiple zones for which user seeks the Temperature Mapping data then the zone numbers should be seperated by          commas(,) as shown in Line 53.

B. Python file: csv-file.py

  The transcript file obtained from FLUENT has redundant lines, and the data in the file is of type 'string' (even the digits). The python   file removes lines with alphabets and converts data type to float. 
  
