#!/usr/bin/python
import pddl, instantiate
import sys

def task_to_prop_strips_domain( task, atoms, actions, axioms ) :
	if len(axioms) > 0 : 
		print >> sys.stdout, "Resulting domain has derived predicates!"
		print >> sys.stdout, "Bailing out!"
		sys.exit(1)
	outstream = open( "%s-dom-prop.pddl"%task.domain_name, "w" ) 
	print >> outstream, "(define (domain %s)"%task.domain_name
	print_requirements( task, outstream )
	print_types( task, outstream )
	print_constants( task, outstream )
	print_predicates( task, atoms, outstream )
	print_functions( task, outstream )
	print_actions( task, actions, outstream )
	print >> outstream, ")"
	outstream.close()

def print_functions( task, stream ) :
	print >> stream, "\t(:functions"
	print >> stream, "\t\t(total-cost) - number"
	print >> stream, "\t)"

def print_predicates( task, atoms, outstream ) :
	print >> outstream, "\t(:predicates"
	#for atom in atoms :
	#	print >> outstream, "\t\t%s"%atom.to_pddl()
	for pred in task.predicates :
		if pred.name == '=' : continue
		if 'new-axiom@' in pred.name : continue
		print >> outstream, "\t\t%s"%pred.to_pddl()
	print >> outstream, "\t)"

def print_requirements( task, outstream ) :
	print >> outstream, "\t(:requirements"
	reqs = [ ':strips', ':typing', ':equality', ':action-costs' ]
	for r in reqs :
		print >> outstream, "\t\t%s"%r
	print >> outstream, "\t)"

def print_types( task, outstream ) :
	print >> outstream, "\t(:types"
	for t in task.types :
		if t.basetype_name is not None :
			print >> outstream, "\t\t%s - %s"%( t.name, t.basetype_name )	
		else :
			print >> outstream, "\t\t%s"%t.name
	print >> outstream, "\t)"

def print_constants( task, outstream ) :
	print >> outstream, "\t(:constants"
	for obj in task.objects :
		print >> outstream, "\t\t%s - %s"%(obj.name, obj.type)	
	print >> outstream, "\t)"

def print_action_precondition( task, a, stream ) :
	print >> stream, "\t\t:precondition"
	if not isinstance( a.precondition, list ) :
		print >> sys.stderr, "Precondition of", a.name, "is not a list"
		print >> sys.stderr, a.precondition
		sys.exit(1)
	print >> stream, "\t\t\t(and"
	for c in a.precondition :
		if not isinstance( c, pddl.conditions.Literal ) :
			print >> sys.stderr, "Problem writing action", a.name, "precondition"
			print >> sys.stderr, c, "is not a literal"	
			sys.exit(1)
		print >> stream, "\t\t\t\t%s"%c.to_pddl()
	print >> stream, "\t\t\t)"	

def print_action_effects( task, a, stream ) :
	print >> stream, "\t\t:effect"
	print >> stream, "\t\t\t(and"
	for condition, literal in a.add_effects :
		if len(condition) == 0 :
			print >> stream, "\t\t\t\t%s"%literal.to_pddl()
		else :
			print >> stream, "\t\t\t\t(when"
			print >> stream, "\t\t\t\t\t(and"
			for c in condition :
				if not isinstance( c, pddl.conditions.Literal ) :
					print >> sys.stderr, "Problem writing action", a.name, "conditional effect"
					print >> sys.stderr, c, "is not a literal"	
					sys.exit(1)
				print >> stream, "\t\t\t\t\t\t%s"%c.to_pddl()
				
			print >> stream, "\t\t\t\t\t)"
			print >> stream, "\t\t\t\t\t%s"%literal.to_pddl()
			print >> stream, "\t\t\t\t)"
	for condition, literal in a.del_effects :
		if len(condition) == 0 :
			print >> stream, "\t\t\t\t%s"%literal.negate().to_pddl()
		else :
			print >> stream, "\t\t\t\t(when"
			print >> stream, "\t\t\t\t\t(and"
			for c in condition :
				if not isinstance( c, pddl.conditions.Literal ) :
					print >> sys.stderr, "Problem writing action", a.name, "conditional effect"
					print >> sys.stderr, c, "is not a literal"	
					sys.exit(1)
				print >> stream, "\t\t\t\t\t\t%s"%c.to_pddl()
				
			print >> stream, "\t\t\t\t\t)"
			print >> stream, "\t\t\t\t\t%s"%literal.negate().to_pddl()
			print >> stream, "\t\t\t\t)"

	cost = a.cost
	if a.cost == 0 :
		a.cost = 1
	print >> stream, "\t\t\t\t(increase (total-cost) %s)"%a.cost
	print >> stream, "\t\t\t)"

def print_actions( task, actions, outstream ) :
	for act in actions :
		print >> outstream, "\t(:action %s"%act.name.replace(' ','_').replace(')','').replace('(','')
		print >> outstream, "\t\t:parameters ()"
		print_action_precondition( task, act, outstream )
		print_action_effects( task, act, outstream )
		print >> outstream, "\t)"

def write_init( task, atoms, outstream ) :
	print >> outstream, "\t(:init"
	print >> outstream, "\t\t(= (total-cost) 0)"
	#I = {}
	for fact in task.init :
		if fact.predicate == '=' : continue
		print >> outstream, "\t\t%s"%fact.to_pddl()
		#I[fact] = True
	#for a in atoms :
	#	if a.predicate == '=' : continue
	#	if 'new-axiom@' in a.predicate : continue
	#	try :
	#		b = I[a]
	#	except KeyError :
	#		print >> outstream, "\t\t%s"%a.negate().to_pddl()
	print >> outstream, "\t)"

def write_goal( task, triv_axioms, outstream ) :
	orig_goal = task.goal
	if not isinstance( orig_goal, pddl.conditions.Conjunction ) :
		print >> sys.stderr, "Task goal not in conjunctive form, bailing out!"
		orig_goal.dump()
		sys.exit(1)
	new_goal_conjuncts = []
	for c in orig_goal.parts :
		if not isinstance( c, pddl.conditions.Literal ) :
			print >> sys.stderr, "Composite!"
			orig_goal.dump()
			sys.exit(1)
		try :
			surrogates = triv_axioms[c.negate()]
			new_goal_conjuncts += [ surr.negate() for surr in surrogates]
		except KeyError :
			new_goal_conjuncts.append( c )
	#new_goal = pddl.conditions.Conjunction( new_goal_conjuncts )
	print >> outstream, "\t(:goal"
	print >> outstream, "\t\t(and"
	for c in new_goal_conjuncts :
		print >> outstream, "\t\t\t", c.to_pddl()
	print >> outstream, "\t\t)"
	#print >> outstream, "\t\t", new_goal.to_pddl()
	print >> outstream, "\t)"

def task_to_prop_strips_problem( task, atoms, trivial_axioms ) :
	output_filename = '%s-prob-prop.pddl'%task.task_name
	outstream = open( output_filename, 'w' )
	print >> outstream, "(define (problem %s)"%task.task_name
	print >> outstream, "\t(:domain %s)"%task.domain_name
	write_init( task, atoms, outstream )
	write_goal( task, trivial_axioms, outstream )	
	print >> outstream, "\t(:metric minimize (total-cost))"
	print >> outstream, ")"
	outstream.close()	

def main() :
	task = pddl.open()
	relaxed_solvable, atoms, actions, axioms = instantiate.explore(task)
	#for action in actions :
	#	action.dump()
	not_trivial_axioms = []
	trivial_axioms = {}
	for axiom in axioms :
		if len(axiom.condition) > 1 :
			not_trivial_axioms.append( axiom )
			continue
		if not isinstance( axiom.effect, pddl.conditions.Literal ) :
			not_trivial_axioms.append( axiom )
			continue
		if isinstance( axiom.effect, pddl.conditions.NegatedAtom ) :
			not_trivial_axioms.append( axiom )
			continue
		try :
			trivial_axioms[ axiom.effect ].append( axiom.condition[0] )
		except KeyError :
			trivial_axioms[ axiom.effect ] = [ axiom.condition[0] ]
	print >> sys.stdout, "Non-trivial axioms:", len(not_trivial_axioms)
	print >> sys.stdout, "Trivial axioms:", len(trivial_axioms.keys())	
	if not relaxed_solvable :
		print >> sys.stdout, "Problem is unsolvable!"
		sys.exit(1)
	task_to_prop_strips_domain( task, atoms, actions, not_trivial_axioms  )
	task_to_prop_strips_problem( task, atoms, trivial_axioms )

if __name__ == '__main__' :
	main()
