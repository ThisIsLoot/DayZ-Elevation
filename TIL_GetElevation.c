class TIL_GetElevation // "TIL" stands for ThisIsLoot
{

	static string TIL_Elevation_version = "0.005";
	
	string getVersion(){
		return TIL_Elevation_version;	
	}
	
	void TIL_getElevation(){
		
		string outputPath = "$profile:ThisIsLootTools/ElevationData/ElevationData.json"; // establish the path for the output file
		
		FileHandle outputFile;
		
		outputFile = OpenFile(outputPath, FileMode.APPEND);
		
		FPrintln(outputFile, "["); // start the json file
		
		float worldSize = GetGame().GetWorld().GetWorldSize(); // get the size of the world. This is the x and z max in meters (e.g. 15000)
		Print("World Size: " + worldSize);
		
		vector position = "0 0 0"; // starting position. Bottom left corner. 
		
		float x = position[0]; // have to use these because we can't use operators on the vector directly...
		float z = position[2]; // have to use these because we can't use operators on the vector directly...
		
		float scanResolution = 10; // the resolution for each step of the scan in meters
		
		float numPoints = (worldSize / scanResolution) * (worldSize / scanResolution);
		
		Print("Performing scan of " + numPoints + "points...");
				
		// while z is less than or equal to the max z, scan the rows
		while(position[2] <= worldSize){
			
			// while x is less than or equal to the max x, scan the columns
			while(position[0] <= worldSize){
				// get the surface level y (i.e. altitude) at the provided x,z position
				float surfaceY = GetGame().SurfaceY(position[0], position[2]);
				
				// JSONify the data using the json serializer
				JsonSerializer m_dataserializer = new JsonSerializer; // New instance of the json serializer
				
				TIL_jsonElevationData m_TIL_jsonElevationData = new TIL_jsonElevationData; // new instance of the TIL_jsonElevationData class (see below for that class)
				
				// data for json
				m_TIL_jsonElevationData.x = position[0];
				m_TIL_jsonElevationData.y = surfaceY;
				m_TIL_jsonElevationData.z = position[2];
				
				string TIL_jsonData; // Empty string to hold jsonified data
				
				//serialize the data (class to jsonify-see below, bool make it human readable, string output-see above)
				bool ok =  m_dataserializer.WriteToString(m_TIL_jsonElevationData , true, TIL_jsonData);
				
				// had this print the data for each point to debug initially. Commented it out for the final run because it crashed Workbench.
				//if(ok){
				//	Print(TIL_jsonData);
				//}
				
				FPrintln(outputFile, TIL_jsonData+","); // append the entry to the json file

				x += scanResolution; // x right to the next column
				position[0] = x; // set the vector to the new x value
			}
		
			z += scanResolution; // z up to the next row
			position[2] = z; // set the vector to the new z value
			
			x = 0; // x back to the origin 'column'
			position[0] = x; // set the vector to the new x value
		}
		
		FPrintln(outputFile, "]"); // end the json file
		CloseFile(outputFile); // close the output file
		Print("Finished.");
						
	}

}

class TIL_jsonElevationData //a class to json serialize into to jsonify the data
{
	float x;
	float y;
	float z;
}
