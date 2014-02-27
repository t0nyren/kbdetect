#include "encoder.h"
#include "detector.h"

class Recognizer{
	public:
		Recognizer(int patchSize = 48, int cellSize = 8, int descrSize = 58);
		void buildModel(const char* dirname, const char* filename, const char* outdir = NULL);
		void loadModel(const char* filename);
		
	private:
		Detector* detector;
		Encoder* encoder;
		
};