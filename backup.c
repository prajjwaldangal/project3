char * c_dig = (char *) malloc(sizeof(char)*(j-t));
		int k=t; // k -> "local var"
		while(k < j) {
			c_dig[k-t] = s[k];
			k += 1;
		}		
		int dig = atoi(c_dig);
		free(c_dig);
