## Additional requirements for the map file (.osm)

* a relation of type "reference", containing a node of role "origin".
* a relation of type "reference", containing a series of nodes of role "boundary". The boundary points must be specified in clockwise order.
* a relation of type "center_line", containing a series of nodes of role "point" and a path of role "line". The name should be "cl_<lanelet-name>"

Example:

```
<relation id='-39216' action='modify'>
    <member type='node' ref='-39134' role='origin' />
    <tag k='type' v='reference' />
</relation>

<relation id='-39871' action='modify'>
    <member type='node' ref='-39124' role='boundary' />
    <member type='node' ref='-39122' role='boundary' />
    ...
    <tag k='type' v='reference' />
  </relation>
```