#define MAX_SUB 1000
#define MAX_FILESIZE 1000000
#define ORIGINAL 1
#define MODIFIED 2

struct RESULT {
    int count;
    int diff[MAX_SUB];
};

extern int get(int file, int index);

int oFile[MAX_FILESIZE];
int mFile[MAX_FILESIZE];
RESULT result;
int oSize;
int missed;

void init()
{
    for (int i=0;i<MAX_FILESIZE;++i)
    {
        oFile[i] = -1;
        mFile[i] = -1;
    }
    result.count = 0;
	missed = 0;
}

int finddiff(int s, int e)
{
	//Just in case end of file size is calculated incorrectly, so offset by -1
	if (oFile[e] == -1)
        oFile[e] = get(ORIGINAL, e);
	if (oFile[e] == 0)
	{
        oFile[e-1] = get(ORIGINAL, e-1);
		e--;
	} 
	
	//Check for Difference
    if (s == e)
    {
        if (oFile[s] == -1)
        {
            oFile[s] = get(ORIGINAL, s);
        }

        if (mFile[s - missed] == -1)
        {
            mFile[s - missed] = get(MODIFIED, s - missed);
        }

        if (oFile[s] != mFile[s - missed])
        {
            result.diff[result.count++] = oFile[s];
            missed++;
            return s + 1;
        }
        return -1;
    }

	//Check for End Position
	if (oFile[e] == -1)
        oFile[e] = get(ORIGINAL, e);
	if (mFile[e - missed] == -1)
		mFile[e - missed] = get(MODIFIED, e - missed);
	if (oFile[e] == mFile[e - missed])
		return 0;


	//Check for mid position
    int mid = s + ((e-s)/2);

    if (oFile[mid] == -1)
        oFile[mid] = get(ORIGINAL, mid);
	if (mFile[mid - missed] == -1)
		mFile[mid - missed] = get(MODIFIED, mid - missed);

	if (oFile[mid] == mFile[mid - missed])
	{	
		//Mid Position Match so we move to next mid + 1
		finddiff(mid+1, e); 
	}
	else
	{	//Mid Position don't match so to start
		finddiff(s, mid); 
		finddiff (mid+1, e); 
	}
	return 0;
}

int findfilesize(int s, int e)
{
	int mid;

	while (1)
	{
		mid = s + ((e - s) / 2);
		if (oFile[mid] == -1)
			oFile[mid] = get(ORIGINAL, mid);

		if (oFile[mid] == 0)
			e = mid-1;
		else
			s = mid+1;

		if (s > e)
			return s+1;
		if (s == e)
			return s;
	};
}

RESULT diff()
{
	//Reset All
	init();
	oSize = findfilesize(0, MAX_FILESIZE-1);
	finddiff(0, oSize);
	return result;
}
