Taxonomy View Switcher Overview
This module allows different views to be shown for different taxonomy terms.
It redirects the display of the current term page to a view based on the 
request_path value (ie the visible url) rather than the aliased url.

--------------------------------------------------------------------------------
Usage scenarios:
Lets say you have a taxonomy defined that contains top level terms of
products, news and downloads and you would like to use different views for each 
category of content.

You could create a set of views with paths matching your taxoomy terms and Taxonomy View Switcher
would take of redirecting 'taxonomy/term/%' to the appropriate view:

For example, views with paths like:

  switch/products/%
  switch/products/subcategory/%
  switch/news%

Would provide different views products and news. A different view again for products/subcategory
(although product/othersubcategories would use the products view.

Downloads would use the default path of 'switch/taxonomy/term/%'


--------------------------------------------------------------------------------
How do you use it:

1: Enable Taxonomy View Switcher module (requires taxonomy and views)

2. Enable the default "Taxonomy Term" view (and / or clone this view if you like)

3. Change the path of the Taxonomy Term view to 'switch/taxonomy/term/%'
   (If you leave the path as the default taxonomy/term/% the views module will 
   override Taxonomy View Switcher and prevent it from working)

   Taxonomy View Switcher will now use the first view it finds with a path of 
  'switch/taxonomy/term/%' as the default view for the term page. 
  (This mirrors the standard behaviour of enabling the Taxonomy Term view)

4. Lets say you'd like the "products" term (and it's child terms) to use
   a different view than the default.
   
   Simply create your new view (it needs to have term id and optionally depth as arguments)
   and give it a path of say 'switch/my-term-url/%'

   In the case of the products node, assuming the url for the term was 'products', the path
   would be 'switch/products/%'

   The 'switch' part identifies the view to Taxonomy View Switcher and prevents conflicts
   with any other urls. 

   Taxonomy View Switcher then matches the request_path (ie the unaliased url) 
   eg http://mysite.com/products/subcategory against all the enabled view display paths to find a suitable 
   view display. It uses the most specific matching path it can find. 
   ie path='switch/products/subcategory/%' would be preferred over 'switch/products/%' for the above url.

   You also need to include the '%' to indicate that the view has 
   arguments - otherwise the view will not be found by Taxonomy View Switcher.

--------------------------------------------------------------------------------
Theming

There are no theming options as Taxonomy View Switcher only redirects output
to the relevant view.

--------------------------------------------------------------------------------
Notes:

1: Taxonomy View Switcher has not been tested with multiple term displays. 
   ex. taxonomy/term/4+6+7 and it probably won't work if you try it.
   (ie it probably breaks any multiple term displays on your site?)

2: Taxonomy View Switcher does not care what your view does however TVI will pass the term id and 
   term id with depth modifier to the view as arguments.  To make use of these, 
   simply add the following arguments to the view you plan to use on your term
   or vocabulary:
   
   A1: Taxonomy: Term ID (with depth)
   A2: Taxonomy: Term ID depth modifier
   
3: Taxonomy View Switcher only looks for "page" displays

4: Taxonomy View Switcher uses hook_menu_alter to replace the taxonomy/term/* callback. Unlike 
   the re-direct method, which causes your server to be queried 2 or more 
   times for each request, the hook_menu_alter method conserves your server 
   resources. 

5. Taxonomy View Switcher is based significantly on the Drupal 7 port of TVI: Taxonomy Views Integration
   but is simpler and to me works in more intuitive way. 
   
--------------------------------------------------------------------------------


   
