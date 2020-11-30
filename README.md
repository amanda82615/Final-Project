# Final-Project

COURSE PROJECT IS 20% OF THE COURSE GRADE

In this project, you will create a system to manage the routes of an airline. 

The airline has provided a file containing the destinations. 

Read the places and destinations from the file (use a suitably enhanced 'place' struct). 
Create linked place-nodes.
Calculate the aerial distance of each link from the destination co-ordinates.  
Store the distance in the origin node in the d_link1, d_link2 variables. 

Provide the user the following menu items:

Prompt for removing a link:

Remove the specified link.
Set the distance of that link to 0 in the origin node. 

Prompt for adding or changing a link:

Set the new link. 

Calculate aerial distance to the new link from the destination co-ordinates. 
Set the distance in the d_link1 / d_link2 variable of the origin node. 

Prompt for finding route between two places: 

Input origin and destination. Find route from origin to destination, via other places if required. There may be more than one route between the specified origin and destination.  


Report all routes found by: a) increasing number of hops
                                               b) increasing distance in miles 

When adding and removing links, the following business rules have to be followed: 

1. Every place should have at least one incoming link and one outgoing link. 

2. The number of outgoing links should not be more than the number of incoming links. 

Develop a console application in C++ that meets the above requirements. Upload it to your GitHub repository. Submit your code as a text file. 

We will review your work on Zoom during regular class hours on Monday 30th Nov, 7th Dec, 14th Dec. The reviews will count towards the project grade and are worth a 40 + 30 + 30 points (in addition to the project grade of 100 points). PLEASE BE READY AT 2:00 PM ON 14th Dec. WITH YOUR COMPLETED PROJECT.

Also complete the Practical Exposure document before class on 14th Dec. This is a separate link in Canvas and is worth its own 100 points.

Points will be awarded as follows:
Read the file and populate the place structs - 10
Link all the destinations - 10
Calculate the aerial distance of each link - 10
Remove the specified link - 15
Adding or changing a link - 15
Finding route between two places - 20

Sorting the routes between two places by increasing order of number of hops, distance in miles - 20

Your application must include at least one file, one function, one struct, one pointer, one array and one header file. Each one that is missing in your application will cost 5 points. SUBMIT YOUR CODE AS A TEXT FILE. 

struct place{

int pcode;

string pname;

double plat;

double plng;

double d_link1;

double d_link2;

place* link1;

place* link2;

}; 
