#include "input.c"
#include "encoder.c"
#include "decoder.c"

/**
 * Entry point for CS4220 Project 1.
 
 * @arg 	This code takes one argument: a path to a text file
 * 			containing a single byte string.
 *
 * @author	Jessop, 	Thomas
 * @author	Rawlins, 	Matthew
 * @author	Worsham,	James
 */
int main(int argc, char * argv[]) {
	// Sanitize input
	if (argc < 2) {
		printf("[ERROR]\tUsage: main.o [input file]");
		return -1;
	}

	// Get the data and encode / decode it
	char * file_path = argv[1];
	char * original_data = readf(file_path);
	
	// Sanitize the input to ensure we have byte string data
	char sanitized = sanitize_input(original_data);
	if (sanitized != '0') {
		printf("\n[ERROR]\tNon binary data found in input string: '%c'", sanitized);
		free(original_data);
		return -1;
	}
	
	// Now encode and decode data
	char * encoded_data = encode(original_data);
	char * decoded_data;

	// Print out the results
	printf("\n[RESULTS]\n");
	printf("\tOriginal: \t%s\n", original_data);
	printf("\tEncoded data: \t%s\n", encoded_data);

	// Flag for user-changed encoded data
	char ans;
	printf("\tChange the encoded data piped to decoder? [y|n] ");
	scanf("%c", &ans);
	getchar();

	// Logic to determine if changes are needed
	if (ans == 'Y' || ans == 'y') {
		printf("\tNew encoded value: ");
		fgets(encoded_data, 13, stdin);
		encoded_data[12] = 0;
	}

	// Now get the decoded data
	decoded_data = decode(encoded_data);
	printf("\tDecoded data: \t%s\n", decoded_data);

	// Free up allocated memory
	free(original_data);
	free(encoded_data);
	free(decoded_data);

	return 0;
}
